#include "cpp_handler.h"
#include "console_lib.h"
#include "event_hook.h"
#include "memory_lib.h"

#include "kh_interface.h"

#include <format>
#include <toml++/toml.h>
#include <unordered_map>

namespace fs = std::filesystem;

typedef void(__cdecl *OnLoadFunc)();
typedef void(__cdecl *OnInitFunc)();
typedef void(__cdecl *OnFrameFunc)();

typedef void(__cdecl *OnGetHitFunc)(KHGameObject *gameobject);
typedef void(__cdecl *OnAttackFunc)(KHGameObject *gameobject);
typedef void(__cdecl *OnGetRewardFunc)(DWORD64 treasure_id);

const std::string loaded_mods_path = "KHMemoryHook/loaded_mods";

//std::vector<OnFrameFunc> on_frame_funcs;
//std::vector<OnGetHitFunc> on_get_hit_funcs;
//std::vector<OnGetRewardFunc> on_get_reward_funcs;
//
//std::vector<HMODULE> loaded_mods;

struct KHMod {
	HMODULE module;
	OnFrameFunc on_frame;
	OnGetHitFunc on_get_hit;
	OnAttackFunc on_attack;
	OnGetRewardFunc on_get_reward;
};
std::vector<KHMod> loaded_mods;

void on_frame_cpp() {
	update_loaded_gameobject_addresses();
	for (const auto &mod : loaded_mods) {
		if (mod.on_frame) {
			mod.on_frame();
		}
	}
}

void on_get_reward_cpp(CONTEXT *ctx) {
	for (const auto &mod : loaded_mods) {
		if (mod.on_get_reward) {
			mod.on_get_reward(ctx->Rcx);
		}
	}
}

void on_get_hit_cpp(CONTEXT *ctx) {
	for (const auto &mod : loaded_mods) {
		if (mod.on_get_hit) {
			mod.on_get_hit(kh_gameobject_init(static_cast<uint64_t>(ctx->Rsi)));
		}
	}
}

void on_attack_cpp(CONTEXT *ctx) {
	for (const auto &mod : loaded_mods) {
		if (mod.on_attack) {
			mod.on_attack(kh_gameobject_init(static_cast<uint64_t>(ctx->Rcx)));
		}
	}
}

bool api_init_cpp(uint64_t base_address, const std::filesystem::path &path) {
	try {
		auto offsets = toml::parse_file(path.u8string());


		MemoryLib::base_4to8 = reinterpret_cast<uintptr_t *>(base_address + offsets["memory"]["base_4to8"].value_or(0));

		uint64_t loaded_gameobjects_address = base_address + offsets["scene"]["loaded_gameobjects"].value_or(0);
		print_message_line(std::format("Loaded GameObjects Address: 0x{:X}", loaded_gameobjects_address), MESSAGE_NONE);
		loaded_gameobjects_start_pointer = reinterpret_cast<uint64_t *>(loaded_gameobjects_address);

		
		install_event_hook(base_address, offsets["events"]["on_get_hit"]["address"].value_or(0), offsets["events"]["on_get_hit"]["size"].value_or(0), on_get_hit_cpp);
		install_event_hook(base_address, offsets["events"]["on_attack"]["address"].value_or(0), offsets["events"]["on_attack"]["size"].value_or(0), on_attack_cpp);
		//install_event_hook(base_address, offsets["events"]["on_get_reward"]["address"].value_or(0), offsets["events"]["on_get_reward"]["size"].value_or(0), on_get_reward_cpp);

	} catch (const std::exception &e) {
		print_message_line(std::format("Error parsing TOML file: {}", e.what()), MESSAGE_ERROR);
		return false;
	}

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
			print_message_line("Mod Setup (on_init) successful!\n", MESSAGE_SUCCESS);
		} else {
			print_message_line(std::format("{} has not implemented event: on_init()\n", file_name), MESSAGE_WARNING);
		}

		// Get the address of the on_frame function
		//OnFrameFunc on_frame = (OnFrameFunc)GetProcAddress(h_mod, "on_frame");
		//if (on_frame) {
		//	///on_frame_funcs.push_back((OnFrameFunc)GetProcAddress(h_mod, "on_frame"));
		//	print_message_line("Mod Setup (on_frame) successful!\n", MESSAGE_SUCCESS);
		//} else {
		//	print_message_line(std::format("{} has not implemented event: on_frame()\n", file_name), MESSAGE_WARNING);
		//}

		// Store the handle of the loaded module if you want to use it later
		KHMod mod{h_mod, nullptr, nullptr, nullptr};
		loaded_mods.push_back(mod);
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
					print_message_line(std::format("{} implemented event: on_frame()", file_name), MESSAGE_SUCCESS);
				} else {
					print_message_line(std::format("{} has not implemented event: on_frame()", file_name), MESSAGE_WARNING);
				}

				OnGetHitFunc on_get_hit = (OnGetHitFunc)GetProcAddress(h_mod, "on_get_hit");
				if (on_get_hit) {
					print_message_line(std::format("{} implemented event: on_get_hit()", file_name), MESSAGE_SUCCESS);
				} else {
					print_message_line(std::format("{} has not implemented event: on_get_hit()", file_name), MESSAGE_WARNING);
				}

				OnAttackFunc on_attack = (OnAttackFunc)GetProcAddress(h_mod, "on_attack");
				if (on_get_hit) {
					print_message_line(std::format("{} implemented event: on_attack()", file_name), MESSAGE_SUCCESS);
				} else {
					print_message_line(std::format("{} has not implemented event: on_attack()", file_name), MESSAGE_WARNING);
				}

				OnGetRewardFunc on_get_reward = (OnGetRewardFunc)GetProcAddress(h_mod, "on_get_reward");
				if (on_get_reward) {
					print_message_line(std::format("{} implemented event: on_get_reward()", file_name), MESSAGE_SUCCESS);
				} else {
					print_message_line(std::format("{} has not implemented event: on_get_reward()", file_name), MESSAGE_WARNING);
				}

				print_message_line("", MESSAGE_NONE);
				// Store the handle of the loaded module if you want to use it later
				KHMod mod{h_mod, on_frame, on_get_hit, on_attack, on_get_reward};
				loaded_mods.push_back(mod);
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
	for (KHMod mod : loaded_mods) {
		if (mod.module) {
			std::string dll_path = get_dll_path_from_handle(mod.module);
			if (FreeLibrary(mod.module)) {
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
}

void reload_mods_cpp() {
	unload_mods_cpp();
	load_mod_setup_cpp();
	load_mods_cpp();
	print_message_line("Reload c++ complete\n", MESSAGE_SUCCESS);
}