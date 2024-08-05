#include "lua_exec.h"

#include <memory>
#include <utility>

#include "console_lib.h"
#include "header_text.h"
#include "input.h"
#include "lua_backend.h"

namespace fs = std::filesystem;

static std::vector<fs::path> script_paths;

extern std::unique_ptr<LuaBackend> lua_backend = nullptr;

void reload_mods_lua() {
	std::printf("\n");
	print_message("Reloading...\n\n", MESSAGE_DEFAULT);
	lua_backend = std::make_unique<LuaBackend>(script_paths, MemoryLib::exec_address + MemoryLib::base_address);

	if (lua_backend->loaded_scripts.size() == 0)
		print_message("No scripts found! Reload halted!\n\n", MESSAGE_ERROR);

	print_message("Executing initialization event handlers...\n\n", MESSAGE_DEFAULT);

	for (auto &script : lua_backend->loaded_scripts)
		if (script->init_function) {
			auto result = script->init_function();

			if (!result.valid()) {
				sol::error _err = result;
				print_message(_err.what(), MESSAGE_ERROR);
				std::printf("\n\n");
			}
		}

	print_message("Reload Lua complete!\n\n", MESSAGE_SUCCESS);
}

int entry_lua(int process_id, HANDLE process_handle, std::uint64_t target_address, std::vector<fs::path> new_script_paths) {
	std::cout << get_header_text() << '\n';

	print_message("Initializing LuaEngine v5.0...\n\n", MESSAGE_DEFAULT);
	script_paths = std::move(new_script_paths);

	MemoryLib::extern_process(process_id, process_handle, target_address);

	lua_backend = std::make_unique<LuaBackend>(script_paths, MemoryLib::exec_address + target_address);
	lua_backend->frame_limit = 16;

	if (lua_backend->loaded_scripts.size() == 0) {
		print_message("No scripts were found! Initialization halted!\n\n", MESSAGE_ERROR);
		return -1;
	}

	print_message("Executing initialization event handlers...\n\n", MESSAGE_DEFAULT);

	for (auto &script : lua_backend->loaded_scripts)
		if (script->init_function) {
			auto result = script->init_function();

			if (!result.valid()) {
				sol::error err = result;
				print_message(err.what(), MESSAGE_ERROR);
				std::printf("\n\n");
			}
		}

	print_message("Initialization complete!\n", MESSAGE_SUCCESS);
	print_message("Press 'F1' to reload all scripts, press 'F2' to toggle the console, press 'F3' to set execution frequency.\n\n", MESSAGE_DEFAULT);

	return 0;
}

void execute_lua() {
	for (std::size_t i = 0; i < lua_backend->loaded_scripts.size(); i++) {
		auto &script = lua_backend->loaded_scripts[i];

		if (script->frame_function) {
			auto result = script->frame_function();

			if (!result.valid()) {
				sol::error err = result;
				print_message(err.what(), MESSAGE_ERROR);
				std::printf("\n\n");

				lua_backend->loaded_scripts.erase(lua_backend->loaded_scripts.begin() + i);
			}
		}
	}
}

bool check_lua() {
	auto val = MemoryLib::read_int(0);

	if (val == 0)
		return false;

	return true;
}

int version_lua() {
	return 128;
}
