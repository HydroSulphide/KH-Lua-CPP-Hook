#include "lua_exec.h"

#include <memory>
#include <utility>

#include "console_lib.h"
#include "lua_backend.h"
#include "header_text.h"

namespace fs = std::filesystem;

bool _key_Pressed_F1 = false;
bool _key_Pressed_F2 = false;
bool _key_Pressed_F3 = false;

static std::vector<fs::path> _script_paths;

static bool _show_console = true;
static bool _requested_reset = false;

static std::unique_ptr<LuaBackend> _backend;

void reset_lua() {
	std::printf("\n");
	print_message("Reloading...\n\n", MESSAGE_DEFAULT);
	_backend = std::make_unique<LuaBackend>(_script_paths, MemoryLib::exec_address + MemoryLib::base_address);

	if (_backend->loaded_scripts.size() == 0)
		print_message("No scripts found! Reload halted!\n\n", MESSAGE_ERROR);

	print_message("Executing initialization event handlers...\n\n", MESSAGE_DEFAULT);

	for (auto &_script : _backend->loaded_scripts)
		if (_script->init_function) {
			auto _result = _script->init_function();

			if (!_result.valid()) {
				sol::error _err = _result;
				print_message(_err.what(), MESSAGE_ERROR);
				std::printf("\n\n");
			}
		}

	print_message("Reload complete!\n\n", MESSAGE_SUCCESS);

	_requested_reset = false;
}

int entry_lua(int process_id, HANDLE process_handle, std::uint64_t target_address, std::vector<fs::path> script_paths) {
	std::cout << get_header_text() << '\n';

	print_message("Initializing LuaEngine v5.0...\n\n", MESSAGE_DEFAULT);
	_script_paths = std::move(script_paths);

	MemoryLib::extern_process(process_id, process_handle, target_address);

	_backend = std::make_unique<LuaBackend>(_script_paths, MemoryLib::exec_address + target_address);
	_backend->frame_limit = 16;

	if (_backend->loaded_scripts.size() == 0) {
		print_message("No scripts were found! Initialization halted!\n\n", MESSAGE_ERROR);
		return -1;
	}

	print_message("Executing initialization event handlers...\n\n", MESSAGE_DEFAULT);

	for (auto &_script : _backend->loaded_scripts)
		if (_script->init_function) {
			auto _result = _script->init_function();

			if (!_result.valid()) {
				sol::error _err = _result;
				print_message(_err.what(), MESSAGE_ERROR);
				std::printf("\n\n");
			}
		}

	print_message("Initialization complete!\n", MESSAGE_SUCCESS);
	print_message("Press 'F1' to reload all scripts, press 'F2' to toggle the console, press 'F3' to set execution frequency.\n\n", MESSAGE_DEFAULT);

	return 0;
}

void execute_lua() {
	if (_requested_reset == false) {

		if (GetKeyState(VK_F3) & 0x8000) {
			if (!_key_Pressed_F3) {
				switch (_backend->frame_limit) {
				case 16:
					_backend->frame_limit = 8;
					print_message("Frequency set to 120Hz.\n", MESSAGE_DEFAULT);
					break;
				case 8:
					_backend->frame_limit = 4;
					print_message("Frequency set to 240Hz.\n", MESSAGE_DEFAULT);
					break;
				case 4:
					_backend->frame_limit = 16;
					print_message("Frequency set to 60Hz.\n", MESSAGE_DEFAULT);
					break;
				}
			}
			_key_Pressed_F3 = true;
		} else {
			_key_Pressed_F3 = false;
		}

		if (GetKeyState(VK_F2) & 0x8000) {
			if (!_key_Pressed_F2) {
				if (_show_console) {
					ShowWindow(GetConsoleWindow(), SW_HIDE);
					_show_console = false;
				}

				else {
					ShowWindow(GetConsoleWindow(), SW_RESTORE);
					_show_console = true;
				}
			}
			_key_Pressed_F2 = true;
		} else {
			_key_Pressed_F2 = false;
		}

		if (GetKeyState(VK_F1) & 0x8000) {
			if (!_key_Pressed_F1) {
				_requested_reset = true;
			}
			_key_Pressed_F1 = true;
		} else {
			_key_Pressed_F1 = false;
		}

		for (std::size_t i = 0; i < _backend->loaded_scripts.size(); i++) {
			auto &_script = _backend->loaded_scripts[i];

			if (_script->frame_function) {
				auto _result = _script->frame_function();

				if (!_result.valid()) {
					sol::error _err = _result;
					print_message(_err.what(), MESSAGE_ERROR);
					std::printf("\n\n");

					_backend->loaded_scripts.erase(_backend->loaded_scripts.begin() + i);
				}
			}
		}
	} else
		reset_lua();
}

bool check_lua() {
	auto _int = MemoryLib::read_int(0);

	if (_int == 0)
		return false;

	return true;
}

int version_lua() {
	return 128;
}
