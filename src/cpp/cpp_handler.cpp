#include "cpp_handler.h"
#include "console_lib.h"
#include "kh_characters.h"

#include <format>

#include <toml++/toml.h>

namespace fs = std::filesystem;

typedef void(__cdecl *OnLoadFunc)();
typedef void(__cdecl *OnInitFunc)();
typedef void(__cdecl *OnFrameFunc)();

std::vector<OnFrameFunc> on_frame_funcs;
std::vector<HMODULE> loaded_mods;


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

	return true;
}

void load_mod_setup_cpp() {
	std::string setup_path = "KHMemoryHook/kh_mod_setup.dll";
	std::string file_name = "kh_mod_setup.dll";

	// Load the DLL
	HMODULE h_mod = LoadLibraryA(setup_path.c_str());
	if (h_mod) {
		print_message(std::format("{} loaded", file_name), MESSAGE_SUCCESS);
		// Get the address of the on_load function
		OnLoadFunc on_load = (OnLoadFunc)GetProcAddress(h_mod, "on_load");
		if (on_load) {
			on_load();
		} else {
			print_message(std::format("Failed to find on_load() in {}", file_name), MESSAGE_ERROR);
		}

		// Get the address of the on_init function
		OnInitFunc on_init = (OnInitFunc)GetProcAddress(h_mod, "on_init");
		if (on_init) {
			on_init();
			print_message("Mod Setup successful!\n", MESSAGE_SUCCESS);
		} else {
			print_message(std::format("{} has not implemented event: on_init()\n", file_name), MESSAGE_WARNING);
		}
	} else {
		print_message(std::format("Failed to load {}\n", file_name), MESSAGE_ERROR);
	}
}

void load_mods_cpp() {

	for (const auto &entry : fs::directory_iterator("mods")) {
		if (entry.path().extension() == ".dll") {
			std::string mod_path = entry.path().string();
			std::string file_name = entry.path().filename().string();

			// Load the DLL
			HMODULE h_mod = LoadLibraryA(mod_path.c_str());
			if (h_mod) {
				print_message(std::format("{} loaded", file_name), MESSAGE_SUCCESS);
				// Get the address of the on_load function
				OnLoadFunc on_load = (OnLoadFunc)GetProcAddress(h_mod, "on_load");
				if (on_load) {
					on_load();
				} else {
					print_message(std::format("Failed to find on_load() in {}", file_name), MESSAGE_ERROR);
				}

				// Get the address of the on_init function
				OnInitFunc on_init = (OnInitFunc)GetProcAddress(h_mod, "on_init");
				if (on_init) {
					on_init();
					print_message(std::format("{} initialized", file_name), MESSAGE_SUCCESS);
				} else {
					print_message(std::format("{} has not implemented event: on_init()", file_name), MESSAGE_WARNING);
				}

				// Store the handle of the loaded module if you want to use it later
				loaded_mods.push_back(h_mod);

				OnFrameFunc on_frame = (OnFrameFunc)GetProcAddress(h_mod, "on_frame");
				if (on_frame) {
					on_frame_funcs.push_back((OnFrameFunc)GetProcAddress(h_mod, "on_frame"));
					print_message(std::format("{} implemented event: on_frame()\n", file_name), MESSAGE_SUCCESS);
				} else {
					print_message(std::format("{} has not implemented event: on_frame()\n", file_name), MESSAGE_WARNING);
				}
			} else {
				print_message(std::format("Failed to load {}\n\n", mod_path), MESSAGE_ERROR);
			}
		}
	}
}

void on_frame_cpp() {
	for (const auto &on_frame : on_frame_funcs) {
		on_frame();
	}
}
