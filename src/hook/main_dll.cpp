#include <array>
#include <chrono>
#include <concepts>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <ztd/text.hpp>

#define WIN32_LEAN_AND_MEAN
#include <shlobj.h>
#include <wil/stl.h>
#include <wil/win32_helpers.h>
#include <windows.h>

#define MiniDumpWriteDump MiniDumpWriteDump_
#include <minidumpapiset.h>
#undef MiniDumpWriteDump

#include "cpp_handler.h"
#include "config.h"
#include "game_info.h"
#include "lua_exec.h"
#include "wil_extra.h"
#include "input.h"

// TODO: Remove after init fix.
#include <thread>

namespace fs = std::filesystem;
namespace ranges = std::ranges;

using MiniDumpWriteDumpProc = decltype(&MiniDumpWriteDump_);

using DirectInput8CreateProc = HRESULT(WINAPI *)(HINSTANCE hinst, DWORD dwVersion, LPCVOID riidltf, LPVOID *ppvOut, LPVOID punkOuter);

using GameFrameProc = std::uint64_t(__cdecl *)(void *rcx);

MiniDumpWriteDumpProc write_dump_proc = nullptr;
DirectInput8CreateProc create_proc = nullptr;

GameFrameProc *frame_proc_ptr = nullptr;
GameFrameProc frame_proc = nullptr;

std::optional<Config> config;
std::optional<GameInfo> game_info;

std::uint64_t module_address = 0;
std::uint64_t base_address = 0;

template <ranges::bidirectional_range R>
	requires std::same_as<ranges::range_value_t<R>, std::uintptr_t>
std::optional<std::uintptr_t> follow_pointer_chain(std::uintptr_t start, const R &offsets) {
	std::uintptr_t current = start;

	for (auto it = ranges::begin(offsets); it != ranges::end(offsets); ++it) {
		if (current == 0)
			return {};

		if (it != ranges::end(offsets) - 1) {
			current = *reinterpret_cast<std::uintptr_t *>(current + *it);
		} else {
			current += *it;
		}
	}

	return current;
}

std::uint64_t __cdecl frame_hook(void *rcx) {
	handle_input();
	execute_lua();
	on_frame_cpp();
	update_loaded_gameobjects();
	return frame_proc(rcx);
}

LONG WINAPI crashDumpHandler(PEXCEPTION_POINTERS exceptionPointers) {
	HANDLE file = CreateFileW(L"CrashDump.dmp", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file != INVALID_HANDLE_VALUE) {
		MINIDUMP_EXCEPTION_INFORMATION mdei;

		mdei.ThreadId = GetCurrentThreadId();
		mdei.ExceptionPointers = exceptionPointers;
		mdei.ClientPointers = TRUE;

		(*write_dump_proc)(GetCurrentProcess(), GetCurrentProcessId(), file, MiniDumpNormal, &mdei, 0, 0);

		CloseHandle(file);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

struct SectionInfo {
	std::uintptr_t offset;
	std::size_t size;
};

SectionInfo find_text_section_info() {
	const auto basePtr = std::bit_cast<std::uint8_t *>(module_address);
	const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(basePtr);
	if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		throw std::runtime_error{"DOS header is corrupt"};
	}

	const auto ntHeaderPtr = basePtr + dosHeader->e_lfanew;
	const auto ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS64>(ntHeaderPtr);
	if (ntHeader->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
		throw new std::runtime_error{"NT64 header is invalid"};
	}

	std::optional<SectionInfo> textSection;

	for (WORD i = 0; i < ntHeader->FileHeader.NumberOfSections; i++) {
		const auto sectionHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(ntHeaderPtr + sizeof(IMAGE_NT_HEADERS64) + (i * sizeof(IMAGE_SECTION_HEADER)));

		constexpr char textSectionName[] = ".text";
		if (std::memcmp(reinterpret_cast<char *>(sectionHeader->Name), textSectionName, sizeof(textSectionName) - 1) == 0) {
			textSection = SectionInfo{
				.offset = sectionHeader->VirtualAddress,
				.size = sectionHeader->SizeOfRawData,
			};
		}
	}

	return textSection.value();
}

std::optional<GameFrameProc *> find_fame_proc(const SectionInfo &textInfo) {
	constexpr char sig[] = "\x48\x89\x35\xA7\xB6\x69\x00\x48\x8B\xC6";
	constexpr char mask[] = "\xFF\xFF\xFF\x00\x00\x00\x00\xFF\xFF\xFF";
	static_assert(sizeof(sig) == sizeof(mask));

	const char *textStart = std::bit_cast<const char *>(module_address + textInfo.offset);
	const char *textEnd = textStart + textInfo.size;

	for (const char *p = textStart; p != textEnd - (sizeof(sig) - 1); p++) {
		bool isMatch = true;
		for (std::size_t i = 0; i < sizeof(sig) - 1; i++) {
			if ((p[i] & mask[i]) != (sig[i] & mask[i])) {
				isMatch = false;
				break;
			}
		}

		if (!isMatch)
			continue;

		const auto scanRes = std::bit_cast<std::uintptr_t>(p);
		const auto appPtrAddress = scanRes + 0x7 + *reinterpret_cast<const std::int32_t *>(scanRes + 0x3);
		const auto appPtr = *std::bit_cast<void **>(appPtrAddress);

		if (appPtr == nullptr)
			return std::nullopt;

		const auto vtableAddress = *static_cast<std::uintptr_t *>(appPtr);
		const auto onFrameEntry = vtableAddress + 4 * sizeof(std::uintptr_t);
		return std::bit_cast<GameFrameProc *>(onFrameEntry);
	}

	return std::nullopt;
}

bool hook_game() {
	static_assert(sizeof(std::uint64_t) == sizeof(std::uintptr_t));

	const auto textInfo = find_text_section_info();
	const auto frameProcPtrOpt = find_fame_proc(textInfo);

	if (!frameProcPtrOpt.has_value()) {
		return false;
	}

	frame_proc_ptr = frameProcPtrOpt.value();
	if (*frame_proc_ptr == nullptr)
		return false;

	DWORD originalProt = 0;
	VirtualProtect(frame_proc_ptr, sizeof(frame_proc_ptr), PAGE_READWRITE, &originalProt);
	frame_proc = *frame_proc_ptr;
	*frame_proc_ptr = frame_hook;
	VirtualProtect(frame_proc_ptr, sizeof(frame_proc_ptr), originalProt, &originalProt);

	SetUnhandledExceptionFilter(crashDumpHandler);

	return true;
}

void initialize_console() {
	if (!AllocConsole()) {
		std::cerr << "Failed to allocate console" << std::endl;
		return;
	}

	FILE *p_console_output;
	if (freopen_s(&p_console_output, "CONOUT$", "w", stdout) != 0) {
		std::cerr << "Failed to redirect stdout" << std::endl;
	}
	if (freopen_s(&p_console_output, "CONOUT$", "w", stderr) != 0) {
		std::cerr << "Failed to redirect stderr" << std::endl;
	}

	std::cout << "Console initialized" << std::endl;
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}

DWORD WINAPI entry([[maybe_unused]] LPVOID lpParameter) {
	initialize_console();

	std::wstring modulePathStr;
	wil::GetModuleFileNameW(nullptr, modulePathStr);

	fs::path modulePath = fs::path{modulePathStr};
	fs::path moduleDir = modulePath.parent_path();
	std::wstring moduleNameW = modulePath.filename();

	std::u8string moduleName = ztd::text::transcode(moduleNameW, ztd::text::wide_utf16, ztd::text::utf8, ztd::text::replacement_handler);

	try {
		config = Config::load("LuaBackend.toml");
		auto entry = config->game_info(moduleName);
		if (entry) {
			game_info = *entry;
		} else {
			return 0;
		}

		module_address = (std::uint64_t)GetModuleHandleW(nullptr);
		base_address = module_address + game_info->base_address;

		fs::path gameDocsRoot = [&]() {
			PWSTR docsRootStr;
			SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &docsRootStr);

			return fs::path{docsRootStr} / game_info->game_docs_path_string;
		}();

		std::vector<fs::path> script_paths;
		for (const auto &path : game_info->script_paths) {
			if (path.relative) {
				fs::path gameScriptsPath = gameDocsRoot / path.str;
				if (fs::exists(gameScriptsPath)) {
					script_paths.push_back(gameScriptsPath);
				}
			} else {
				fs::path gameScriptsPath = fs::path{path.str};
				if (fs::exists(gameScriptsPath)) {
					script_paths.push_back(gameScriptsPath);
				}
			}
		}

		if (!script_paths.empty()) {
			if (entry_lua(GetCurrentProcessId(), GetCurrentProcess(), base_address, std::move(script_paths)) == 0) {
				// TODO: Hook after game initialization is done.
				while (!hook_game()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(16));
				}
			} else {
				std::cout << "Failed to initialize KH-Lua-CPP-Hook!" << std::endl;
			}

			// Initialize c++ api
			std::cout << "Base Address: " << std::hex << base_address << std::endl;
			api_init_cpp(base_address, "KHMemoryHook/offsets/kh1/steam.toml");
			load_mod_setup_cpp();
			load_mods_cpp();

			while (true) {
				handle_input_console();
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}
		}
	} catch (std::exception &e) {
		std::string msg = "entry exception: " + std::string(e.what()) + "\n\nScripts failed to load.";
		std::wstring wmsg = ztd::text::transcode(msg, ztd::text::compat_utf8, ztd::text::wide_utf16, ztd::text::replacement_handler);
		MessageBoxW(NULL, wmsg.c_str(), L"KH-Lua-CPP-Hook", MB_ICONERROR | MB_OK);
	}

	return 0;
}

void RunBatchScript(const std::wstring &scriptPath, const std::wstring &args) {
	// Build the command line
	std::wstring commandLine = L"cmd.exe /C \"\"" + scriptPath + L"\" \"" + args + L"\"\"";

	// Set up the STARTUPINFO structure
	STARTUPINFO si = {sizeof(si)};
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWMINIMIZED;

	// Set up the PROCESS_INFORMATION structure
	PROCESS_INFORMATION pi = {0};

	// Convert the command line to a modifiable array of wide characters
	std::vector<wchar_t> commandBuffer(commandLine.begin(), commandLine.end());
	commandBuffer.push_back(L'\0'); // Null-terminate the command line

	// Create the process to run the batch script
	if (!CreateProcess(NULL,				 // No module name (use command line)
					   commandBuffer.data(), // Command line
					   NULL,				 // Process handle not inheritable
					   NULL,				 // Thread handle not inheritable
					   FALSE,				 // Set handle inheritance to FALSE
					   CREATE_NEW_CONSOLE,	 // Create a new console window
					   NULL,				 // Use parent's environment block
					   NULL,				 // Use parent's starting directory
					   &si,					 // Pointer to STARTUPINFO structure
					   &pi					 // Pointer to PROCESS_INFORMATION structure
					   )) {
		DWORD errorCode = GetLastError();
		std::wstring errorMessage = L"CreateProcess failed with error code " + std::to_wstring(errorCode);
		MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

BOOL WINAPI DllMain([[maybe_unused]] HINSTANCE hinstDLL, DWORD fdwReason, [[maybe_unused]] LPVOID lpReserved) {
	static HMODULE dbghelp = nullptr;
	static HMODULE dinput8 = nullptr;

	switch (fdwReason) {
	case DLL_PROCESS_ATTACH: {
		std::wstring systemDirectoryStr;
		wil::GetSystemDirectoryW(systemDirectoryStr);
		fs::path dllPath = fs::path{systemDirectoryStr} / L"DBGHELP.dll";

		dbghelp = LoadLibraryW(dllPath.wstring().c_str());
		write_dump_proc = (MiniDumpWriteDumpProc)GetProcAddress(dbghelp, "MiniDumpWriteDump");

		fs::path dinput8Path = fs::path{systemDirectoryStr} / L"DINPUT8.dll";

		dinput8 = LoadLibraryW(dinput8Path.wstring().c_str());
		create_proc = (DirectInput8CreateProc)GetProcAddress(dinput8, "DirectInput8Create");

		if (CreateThread(nullptr, 0, entry, nullptr, 0, nullptr) == nullptr) {
			return FALSE;
		}
		break;
	}
	case DLL_PROCESS_DETACH: { // Path to the batch script
		std::wstring batch_script_path = L"KHMemoryHook\\remove_loaded_mods.bat";
		std::wstring loaded_mods_path = L"KHMemoryHook\\loaded_mods\\";

		// Run the batch script
		RunBatchScript(batch_script_path, loaded_mods_path);

		FreeLibrary(dbghelp);
		FreeLibrary(dinput8);
		break;
	}
	default: break;
	}

	return TRUE;
}

extern "C" __declspec(dllexport) HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, LPCVOID riidltf, LPVOID *ppvOut, LPVOID punkOuter) {
	return create_proc(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

extern "C" __declspec(dllexport) BOOL WINAPI MiniDumpWriteDump(HANDLE hProcess, DWORD ProcessId, HANDLE hFile, MINIDUMP_TYPE DumpType, PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, PMINIDUMP_CALLBACK_INFORMATION CallbackParam) {
	return write_dump_proc(hProcess, ProcessId, hFile, DumpType, ExceptionParam, UserStreamParam, CallbackParam);
}
