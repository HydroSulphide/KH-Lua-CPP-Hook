#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#define WIN32_LEAN_AND_MEAN
#include <psapi.h>
#include <shlobj.h>
#include <tlhelp32.h>
#include <wil/stl.h>
#include <wil/win32_helpers.h>
#include <windows.h>

#include "wil_extra.h"

class MemoryLib {
  private:
	static inline STARTUPINFOW _s_info;
	static inline PROCESS_INFORMATION _p_info;
	static inline bool _big_endian = false;

	class ProtectLock {
	  private:
		std::uintptr_t address;
		std::size_t size;
		DWORD protection;
		bool is_acquired;

	  public:
		ProtectLock(std::uintptr_t address, std::size_t size) : address(address), size(size), protection(0), is_acquired(false) {
			if (VirtualProtect((void *)address, size, PAGE_READWRITE, &protection) != 0)
				is_acquired = true;
		}

		~ProtectLock() {
			if (good())
				VirtualProtect((void *)address, size, protection, &protection);
		}

		bool good() const noexcept { return is_acquired; }
	};

  public:
	static inline std::uint64_t exec_address;
	static inline std::uint64_t base_address;
	static inline std::uint64_t *base_4to8;
	static inline DWORD p_identifier = 0;
	static inline HANDLE p_handle = NULL;
	static inline std::wstring p_name;

	static HMODULE find_base_address(HANDLE input_handle, std::wstring input_name) {
		HMODULE h_mods[1024];
		DWORD cb_needed;
		unsigned int i;

		if (EnumProcessModules(input_handle, h_mods, sizeof(h_mods), &cb_needed)) {
			for (i = 0; i < (cb_needed / sizeof(HMODULE)); i++) {
				std::wstring sz_mod_name;
				if (wil::GetModuleFileNameExW(input_handle, h_mods[i], sz_mod_name)) {
					if (sz_mod_name.find(input_name) != std::wstring::npos)
						return h_mods[i];
				}
			}
		}

		return nullptr;
	}

	static DWORD find_process_id(const std::wstring &process_name) {
		PROCESSENTRY32 process_info;
		process_info.dwSize = sizeof(process_info);

		HANDLE processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (processes_snapshot == INVALID_HANDLE_VALUE)
			return 0;

		Process32First(processes_snapshot, &process_info);
		if (!process_name.compare(process_info.szExeFile)) {
			CloseHandle(processes_snapshot);
			return process_info.th32ProcessID;
		}

		while (Process32Next(processes_snapshot, &process_info)) {
			if (!process_name.compare(process_info.szExeFile)) {
				CloseHandle(processes_snapshot);
				return process_info.th32ProcessID;
			}
		}

		CloseHandle(processes_snapshot);
		return 0;
	}

	static void set_base_address(std::uint64_t input_address) { base_address = input_address; }

	static int execute_process(std::wstring input_name, std::uint64_t input_address, bool input_endian) {
		ZeroMemory(&_s_info, sizeof(_s_info));
		_s_info.cb = sizeof(_s_info);
		ZeroMemory(&_p_info, sizeof(_p_info));

		if (CreateProcessW(input_name.c_str(), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &_s_info, &_p_info) == 0)
			return -1;

		base_address = input_address;
		_big_endian = input_endian;

		return 0;
	};

	static bool latch_process(std::wstring input_name, std::uint64_t input_address, bool input_endian) {
		ZeroMemory(&_s_info, sizeof(_s_info));
		_s_info.cb = sizeof(_s_info);
		ZeroMemory(&_p_info, sizeof(_p_info));

		p_identifier = find_process_id(std::wstring(input_name.begin(), input_name.end()));
		p_handle = OpenProcess(PROCESS_ALL_ACCESS, false, p_identifier);

		wil_extra::GetProcessImageFileNameW(MemoryLib::p_handle, p_name);
		base_address = input_address;

		exec_address = (std::uint64_t)find_base_address(p_handle, p_name);
		_big_endian = input_endian;

		if (p_handle == NULL)
			return false;

		return true;
	};

	static void extern_process(DWORD input_id, HANDLE input_handle, std::uint64_t input_address) {
		p_identifier = input_id;
		p_handle = input_handle;

		wil_extra::GetProcessImageFileNameW(MemoryLib::p_handle, p_name);

		base_address = input_address;
		exec_address = (std::uint64_t)find_base_address(p_handle, p_name);
	};

	template <typename T, std::enable_if_t<std::is_trivially_constructible_v<T>, int> = 0> static T read_scalar_absolute(std::uint64_t address) {
		ProtectLock lock(address, sizeof(T));
		if (!lock.good())
			return 0;

		return *reinterpret_cast<T *>(address);
	}

	static inline std::uint8_t read_byte_absolute(std::uint64_t address) { return read_scalar_absolute<std::uint8_t>(address); }

	static inline std::uint16_t read_short_absolute(std::uint64_t address) { return read_scalar_absolute<std::uint16_t>(address); }

	static inline std::uint32_t read_int_absolute(std::uint64_t address) { return read_scalar_absolute<std::uint32_t>(address); }

	static inline std::uint64_t read_long_absolute(std::uint64_t address) { return read_scalar_absolute<std::uint64_t>(address); }

	static inline float read_float_absolute(std::uint64_t address) { return read_scalar_absolute<float>(address); }

	static inline bool read_bool_absolute(std::uint64_t address) { return read_byte_absolute(address) != 0; }

	static std::vector<std::uint8_t> read_bytes_absolute(std::uint64_t address, int length) {
		std::vector<std::uint8_t> _buffer;

		ProtectLock lock(address, static_cast<std::size_t>(length));
		if (lock.good()) {
			_buffer.resize(length);
			std::memcpy(_buffer.data(), (void *)address, length);
		}

		return _buffer;
	}

	static std::string read_string_absolute(std::uint64_t address, int length) {
		std::string _output;

		ProtectLock lock(address, static_cast<std::size_t>(length));
		if (lock.good()) {
			_output.resize(length);
			std::memcpy(_output.data(), (void *)address, length);
		}

		return _output;
	}

	template <typename T> static T read_scalar(std::uint64_t address, bool absolute = false) {
		if (absolute) {
			return read_scalar_absolute<T>(address);
		} else {
			return read_scalar_absolute<T>(address + base_address);
		}
	}

	static inline std::uint8_t read_byte(std::uint64_t address, bool absolute = false) { return read_scalar<std::uint8_t>(address, absolute); }

	static inline std::uint16_t read_short(std::uint64_t address, bool absolute = false) { return read_scalar<std::uint16_t>(address, absolute); }

	static inline std::uint32_t read_int(std::uint64_t address, bool absolute = false) { return read_scalar<std::uint32_t>(address, absolute); }

	static inline std::uint64_t read_long(std::uint64_t address, bool absolute = false) { return read_scalar<std::uint64_t>(address, absolute); }

	static inline float read_float(std::uint64_t address, bool absolute = false) { return read_scalar<float>(address, absolute); }

	static inline bool read_bool(std::uint64_t address, bool absolute = false) { return read_byte(address, absolute) != 0; }

	static std::vector<std::uint8_t> read_bytes(std::uint64_t address, int length, bool absolute = false) {
		if (absolute) {
			return read_bytes_absolute(address, length);
		} else {
			return read_bytes_absolute(address + base_address, length);
		}
	}

	static std::string read_string(std::uint64_t address, int length, bool absolute = false) {
		if (absolute) {
			return read_string_absolute(address, length);
		} else {
			return read_string_absolute(address + base_address, length);
		}
	}

	template <typename T, std::enable_if_t<std::is_trivially_copy_assignable_v<T>, int> = 0> static void write_scalar_absolute(std::uint64_t address, T t) {
		ProtectLock lock(address, sizeof(T));
		if (!lock.good())
			return;

		*reinterpret_cast<T *>(address) = t;
	}

	static inline void write_byte_absolute(std::uint64_t address, std::uint8_t input) { write_scalar_absolute<std::uint8_t>(address, input); }

	static inline void write_short_absolute(std::uint64_t address, std::uint16_t input) { write_scalar_absolute<std::uint16_t>(address, input); }

	static inline void write_int_absolute(std::uint64_t address, std::uint32_t input) { write_scalar_absolute<std::uint32_t>(address, input); }

	static inline void write_long_absolute(std::uint64_t address, std::uint64_t input) { write_scalar_absolute<std::uint64_t>(address, input); }

	static inline void write_float_absolute(std::uint64_t address, float input) { write_scalar_absolute<float>(address, input); }

	static inline void write_bool_absolute(std::uint64_t address, bool input) { write_byte_absolute(address, input ? 1 : 0); }

	static void write_bytes_absolute(std::uint64_t address, std::vector<std::uint8_t> input) {
		ProtectLock lock(address, input.size());
		if (lock.good())
			std::memcpy((void *)address, input.data(), input.size());
	}

	static void write_string_absolute(std::uint64_t address, std::string input) {
		ProtectLock lock(address, input.size());
		if (lock.good())
			std::memcpy((void *)address, input.data(), input.size());
	}

	template <typename T> static void write_scalar(std::uint64_t address, T const &t, bool absolute = false) {
		if (absolute) {
			write_scalar_absolute<T>(address, t);
		} else {
			write_scalar_absolute<T>(address + base_address, t);
		}
	}

	static inline void write_byte(std::uint64_t address, std::uint8_t input, bool absolute = false) { write_scalar<std::uint8_t>(address, input, absolute); }

	static inline void write_short(std::uint64_t address, std::uint16_t input, bool absolute = false) { write_scalar<std::uint16_t>(address, input, absolute); }

	static inline void write_int(std::uint64_t address, std::uint32_t input, bool absolute = false) { write_scalar<std::uint32_t>(address, input, absolute); }

	static inline void write_long(std::uint64_t address, std::uint64_t input, bool absolute = false) { write_scalar<std::uint64_t>(address, input, absolute); }

	static inline void write_float(std::uint64_t address, float input, bool absolute = false) { write_scalar<float>(address, input, absolute); }

	static inline void write_bool(std::uint64_t address, bool input, bool absolute = false) { write_byte(address, input ? 1 : 0, absolute); }

	static void write_bytes(std::uint64_t address, std::vector<std::uint8_t> input, bool absolute = false) {
		if (absolute) {
			write_bytes_absolute(address, std::move(input));
		} else {
			write_bytes_absolute(address + base_address, std::move(input));
		}
	}

	static void write_string(std::uint64_t address, std::string input, bool absolute = false) {
		if (absolute) {
			write_string_absolute(address, std::move(input));
		} else {
			write_string_absolute(address + base_address, std::move(input));
		}
	}

	static void write_exec(std::uint64_t address, std::vector<std::uint8_t> input) {
		ProtectLock lock(address, input.size());
		if (lock.good())
			std::memcpy((void *)(address + exec_address), input.data(), input.size());
	}

	static inline std::uint64_t get_pointer(std::uint64_t address, std::uint64_t Offset, bool absolute = false) {
		std::uint64_t _temp = read_long(address, absolute);
		return _temp + Offset;
	}

	static inline std::uint64_t get_pointer_absolute(std::uint64_t address, std::uint64_t Offset) {
		std::uint64_t _temp = read_long_absolute(address);
		return _temp + Offset;
	}

	static inline std::uint64_t get_4to8_pointer(uint32_t offset) {
		std::uint32_t offset_after_bit_reset = offset & (~(1 << 31)); // alternative: offset & 0x7FFFFFFF

		std::uint32_t offset_after_bit_shift = offset_after_bit_reset >> 0x19;

		std::uint64_t pointer_address = *(base_4to8 + offset_after_bit_shift);

		return pointer_address | (offset & 0x1FFFFFF);
	}
};
