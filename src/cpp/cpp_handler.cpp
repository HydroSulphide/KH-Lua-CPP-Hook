#include "cpp_handler.h"
#include "console_lib.h"
#include "kh_characters.h"

#include <format>
#include <windows.h>

#include <toml++/toml.h>

namespace fs = std::filesystem;

typedef void(__cdecl *OnLoadFunc)();
typedef void(__cdecl *OnInitFunc)();
typedef void(__cdecl *OnFrameFunc)();

const std::string loaded_mods_path = "KHMemoryHook/loaded_mods";

std::vector<OnFrameFunc> on_frame_funcs;
std::vector<HMODULE> loaded_mods;

typedef void (*OriginalFunctionType)();
OriginalFunctionType trampoline = nullptr;
std::vector<BYTE> originalBytes(7); // Size for a 7-byte instruction
bool codeExecuted = false;

void customCodeLogic() {
	std::cout << "CustomCode executed" << std::endl;
	// Additional custom logic here
}

void RestoreOriginalBytes(uintptr_t targetAddress) {
	DWORD oldProtect;
	VirtualProtect((void *)targetAddress, originalBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
	std::cout << "Restoring original bytes at: " << std::hex << targetAddress << std::endl;
	for (size_t i = 0; i < originalBytes.size(); ++i) {
		std::cout << "Byte " << i << ": " << std::hex << std::setw(2) << std::setfill('0') << (int)originalBytes[i] << " ";
	}
	std::cout << std::endl;
	memcpy((void *)targetAddress, originalBytes.data(), originalBytes.size());
	VirtualProtect((void *)targetAddress, originalBytes.size(), oldProtect, &oldProtect);
}

LONG WINAPI CustomCodeHandler(EXCEPTION_POINTERS *pExceptionInfo) {
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) {
		std::cout << "Exception Code: " << std::hex << pExceptionInfo->ExceptionRecord->ExceptionCode << std::endl;
		std::cout << "RIP (before): " << std::hex << pExceptionInfo->ContextRecord->Rip << std::endl;

		// Call your custom logic
		customCodeLogic();

		// Set the flag to indicate code has been executed
		codeExecuted = true;

		// Restore the original bytes
		RestoreOriginalBytes((uintptr_t)pExceptionInfo->ContextRecord->Rip);

		// Adjust RIP to continue after the original instruction
		// The original instruction is 7 bytes long
		// pExceptionInfo->ContextRecord->Rip = pExceptionInfo->ContextRecord->Rip + originalBytes.size();

		// Print adjusted RIP
		std::cout << "RIP (after adjustment): " << std::hex << pExceptionInfo->ContextRecord->Rip << std::endl;

		// Continue execution
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

void InstallHook(uintptr_t base_address) {
	uintptr_t targetAddress = base_address + 0x2A467E; // Address to hook

	// Save the original bytes (full instruction)
	DWORD oldProtect;
	VirtualProtect((void *)targetAddress, originalBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(originalBytes.data(), (void *)targetAddress, originalBytes.size());

	std::cout << "Original bytes at address: " << std::hex << targetAddress << std::endl;
	for (size_t i = 0; i < originalBytes.size(); ++i) {
		std::cout << "Byte " << i << ": " << std::hex << std::setw(2) << std::setfill('0') << (int)originalBytes[i] << " ";
	}
	std::cout << std::endl;

	// Save the original function address
	trampoline = (OriginalFunctionType)targetAddress;

	// Install the exception handler
	HANDLE handler = AddVectoredExceptionHandler(1, CustomCodeHandler);
	if (!handler) {
		std::cerr << "Failed to add vectored exception handler." << std::endl;
		return;
	}

	// Overwrite the target address with an interrupt to trigger the exception handler
	BYTE int3 = 0xCC; // INT 3 instruction
	VirtualProtect((void *)targetAddress, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((BYTE *)targetAddress) = int3;
	VirtualProtect((void *)targetAddress, 1, oldProtect, &oldProtect);

	std::cout << "Hook installed at address: " << std::hex << targetAddress << std::endl;
}

bool api_init_cpp(uintptr_t base_address, const std::filesystem::path &path) {
	auto offsets = toml::parse_file(path.u8string());

	uintptr_t sora_character_stats_address = offsets["character_stats"]["sora"].value_or(0);
	uintptr_t donald_character_stats_address = offsets["character_stats"]["donald"].value_or(0);
	uintptr_t goofy_character_stats_address = offsets["character_stats"]["goofy"].value_or(0);

	uintptr_t sora_field_stats_address = offsets["field_stats"]["sora"].value_or(0);
	uintptr_t donald_field_stats_address = offsets["field_stats"]["donald"].value_or(0);
	uintptr_t goofy_field_stats_address = offsets["field_stats"]["goofy"].value_or(0);

	character_stats_init(base_address, sora_character_stats_address, donald_character_stats_address, goofy_character_stats_address);
	field_stats_init(base_address, sora_field_stats_address, donald_field_stats_address, goofy_field_stats_address);

	InstallHook(base_address);

	return true;
}

void load_mod_setup_cpp() {
	std::string setup_path = "KHMemoryHook/kh_mod_setup.dll";
	std::string file_name = "kh_mod_setup.dll";

	fs::create_directories(loaded_mods_path);
	std::string dest_path = loaded_mods_path + "/kh_mod_setup.dll";
	fs::copy_file(setup_path, dest_path, fs::copy_options::overwrite_existing);

	// Load the DLL
	HMODULE h_mod = LoadLibraryA(dest_path.c_str());
	if (h_mod) {
		print_message_line(std::format("{} loaded", file_name), MESSAGE_SUCCESS);
		// Get the address of the on_load function
		OnLoadFunc on_load = (OnLoadFunc)GetProcAddress(h_mod, "on_load");
		if (on_load) {
			on_load();
		} else {
			print_message_line(std::format("Failed to find on_load() in {}", file_name), MESSAGE_ERROR);
		}

		// Get the address of the on_init function
		OnInitFunc on_init = (OnInitFunc)GetProcAddress(h_mod, "on_init");
		if (on_init) {
			on_init();
			print_message_line("Mod Setup successful!\n", MESSAGE_SUCCESS);
		} else {
			print_message_line(std::format("{} has not implemented event: on_init()\n", file_name), MESSAGE_WARNING);
		}

		// Store the handle of the loaded module if you want to use it later
		loaded_mods.push_back(h_mod);
	} else {
		print_message_line(std::format("Failed to load {}\n", file_name), MESSAGE_ERROR);
	}
}

void load_mods_cpp() {
	for (const auto &entry : fs::directory_iterator("mods")) {
		if (entry.path().extension() == ".dll") {
			std::string mod_path = entry.path().string();
			std::string file_name = entry.path().filename().string();

			fs::create_directories(loaded_mods_path);
			std::string dest_path = loaded_mods_path + "/" + file_name;
			fs::copy_file(mod_path, dest_path, fs::copy_options::overwrite_existing);

			// Load the DLL
			HMODULE h_mod = LoadLibraryA(dest_path.c_str());
			if (h_mod) {
				print_message_line(std::format("{} loaded", file_name), MESSAGE_SUCCESS);
				// Get the address of the on_load function
				OnLoadFunc on_load = (OnLoadFunc)GetProcAddress(h_mod, "on_load");
				if (on_load) {
					on_load();
				} else {
					print_message_line(std::format("Failed to find on_load() in {}", file_name), MESSAGE_ERROR);
				}

				// Get the address of the on_init function
				OnInitFunc on_init = (OnInitFunc)GetProcAddress(h_mod, "on_init");
				if (on_init) {
					on_init();
					print_message_line(std::format("{} initialized", file_name), MESSAGE_SUCCESS);
				} else {
					print_message_line(std::format("{} has not implemented event: on_init()", file_name), MESSAGE_WARNING);
				}

				OnFrameFunc on_frame = (OnFrameFunc)GetProcAddress(h_mod, "on_frame");
				if (on_frame) {
					on_frame_funcs.push_back((OnFrameFunc)GetProcAddress(h_mod, "on_frame"));
					print_message_line(std::format("{} implemented event: on_frame()\n", file_name), MESSAGE_SUCCESS);
				} else {
					print_message_line(std::format("{} has not implemented event: on_frame()\n", file_name), MESSAGE_WARNING);
				}

				// Store the handle of the loaded module if you want to use it later
				loaded_mods.push_back(h_mod);
			} else {
				print_message_line(std::format("Failed to load {}\n", mod_path), MESSAGE_ERROR);
			}
		}
	}
}

std::string get_dll_path_from_handle(HMODULE h_mod) {
	char path[MAX_PATH];
	if (GetModuleFileNameA(h_mod, path, MAX_PATH) != 0) {
		return path;
	}
	return "";
}

std::string get_filename_from_path(const std::string &path) {
	size_t pos = path.find_last_of("\\/");
	if (pos != std::string::npos) {
		return path.substr(pos + 1);
	}
	return "";
}

void unload_mods_cpp() {
	print_message_line("Unloading c++ mod libraries", MESSAGE_DEFAULT);
	for (HMODULE h_mod : loaded_mods) {
		if (h_mod) {
			std::string dll_path = get_dll_path_from_handle(h_mod);
			if (FreeLibrary(h_mod)) {
				print_message_line(std::format("Successfully unloaded \"{}\"", get_filename_from_path(dll_path)), MESSAGE_DEFAULT);

				// Delete the DLL file after unloading
				if (!dll_path.empty() && fs::exists(dll_path)) {
					try {
						fs::remove(dll_path);
						print_message_line(std::format("Successfully deleted \"{}\"", dll_path), MESSAGE_DEFAULT);
					} catch (const fs::filesystem_error &e) {
						print_message_line(std::format("Failed to delete \"{}\": {}", dll_path, e.what()), MESSAGE_ERROR);
					}
				}
			} else {
				print_message_line(std::format("Failed to unload \"{}\"", get_filename_from_path(dll_path)), MESSAGE_ERROR);
			}
		}
	}
	print_message_line("Successfully unloaded c++ mod libraries\n", MESSAGE_SUCCESS);
	loaded_mods.clear();
	on_frame_funcs.clear();
}

void reload_mods_cpp() {
	unload_mods_cpp();
	load_mod_setup_cpp();
	load_mods_cpp();
	print_message_line("Reload c++ complete\n", MESSAGE_SUCCESS);
}

void on_frame_cpp() {
	for (const auto &on_frame : on_frame_funcs) {
		on_frame();
	}
}
