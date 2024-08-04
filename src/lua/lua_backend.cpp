#include "lua_backend.h"

#include <crcpp/CRC.h>

#include <string>
#include <utility>

namespace fs = std::filesystem;

LuaBackend::LuaBackend(const std::vector<fs::path> &script_paths, std::uint64_t base_input) {
	frame_limit = 16;
	load_scripts(script_paths, base_input);
}

int LuaBackend::exception_handle(lua_State *lua_state, sol::optional<const std::exception &> thrown_exception, sol::string_view description) {
	(void)description;

	const std::exception _ex = *thrown_exception;
	print_message(std::string{_ex.what()} + "\n", MESSAGE_ERROR);

	return sol::stack::push(lua_state, _ex.what());
}

void LuaBackend::load_scripts(const std::vector<fs::path> &script_paths, std::uint64_t base_input) {
	loaded_scripts.clear();

	for (auto scriptsDir : script_paths) {
		if (!fs::is_directory(scriptsDir)) {
			continue;
		}

		for (auto _path : fs::directory_iterator(scriptsDir)) {
			auto _script = std::make_unique<LuaScript>();

			// clang-format off
            _script->lua_state.open_libraries(
                sol::lib::base,
                sol::lib::package,
                sol::lib::coroutine,
                sol::lib::string,
                sol::lib::os,
                sol::lib::math,
                sol::lib::table,
                sol::lib::io,
                sol::lib::bit32,
                sol::lib::utf8
            );
			// clang-format on

			_script->lua_state.set_exception_handler(&exception_handle);

			set_functions(&_script->lua_state);

			fs::path _luaPath = scriptsDir / L"io_packages" / L"?.lua";
			fs::path _dllPath = scriptsDir / L"io_packages" / L"?.dll";

			_script->lua_state["package"]["path"] = _luaPath.string();
			_script->lua_state["package"]["cpath"] = _dllPath.string();

			fs::path _loadPath = scriptsDir / L"io_load";

			_script->lua_state["LOAD_PATH"] = _loadPath.string();
			_script->lua_state["SCRIPT_PATH"] = scriptsDir.string();
			_script->lua_state["CHEATS_PATH"] = "NOT_AVAILABLE";

			fs::path _pathFull = MemoryLib::p_name;
			auto _pathExe = _pathFull.filename().string();

			_script->lua_state["ENGINE_VERSION"] = 5;
			_script->lua_state["ENGINE_TYPE"] = "BACKEND";
			_script->lua_state["GAME_ID"] = CRC::Calculate(_pathExe.c_str(), _pathExe.length(), CRC::CRC_32());
			_script->lua_state["BASE_ADDR"] = base_input;

			const auto _filePath = _path.path();
			const auto _filePathStr = _filePath.string();

			if (_filePath.extension() == ".lua") {
				_script->lua_state["LUA_NAME"] = _filePath.filename().string();

				print_message("Found script: \"" + _filePathStr + "\" Initializing...\n", MESSAGE_DEFAULT);

				auto _result = _script->lua_state.script_file(_filePathStr, &sol::script_pass_on_error);

				_script->init_function = _script->lua_state["_OnInit"];
				_script->frame_function = _script->lua_state["_OnFrame"];

				if (_result.valid()) {
					if (!_script->init_function && !_script->frame_function) {
						print_message("No event handlers exist or all of them have errors.\n", MESSAGE_ERROR);
						print_message("Initialization of this script cannot continue...\n", MESSAGE_ERROR);
						return;
					}

					if (!_script->init_function)
						print_message("The event handler for initialization either has errors or does not exist.\n", MESSAGE_WARNING);

					if (!_script->frame_function)
						print_message("The event handler for framedraw either has errors or does not exist.\n", MESSAGE_WARNING);

					print_message("Initialization of this script was successful!\n\n", MESSAGE_SUCCESS);

					loaded_scripts.push_back(std::move(_script));
				} else {
					sol::error err = _result;
					print_message(std::string{err.what()} + "\n", MESSAGE_ERROR);
					print_message("Initialization of this script was aborted.\n", MESSAGE_ERROR);
				}
			}
		}
	}
}

void LuaBackend::set_functions(LuaState *_state) {
	_state->set_function("ReadByte", sol::overload([](std::uint64_t address) -> std::uint8_t { return MemoryLib::read_byte(address, false); }, [](std::uint64_t address, bool absolute) -> std::uint8_t { return MemoryLib::read_byte(address, absolute); }));

	_state->set_function("ReadShort", sol::overload([](std::uint64_t address) -> std::uint16_t { return MemoryLib::read_short(address, false); }, [](std::uint64_t address, bool absolute) -> std::uint16_t { return MemoryLib::read_short(address, absolute); }));

	_state->set_function("ReadInt", sol::overload([](std::uint64_t address) -> std::uint32_t { return MemoryLib::read_int(address, false); }, [](std::uint64_t address, bool absolute) -> std::uint32_t { return MemoryLib::read_int(address, absolute); }));

	_state->set_function("ReadLong", sol::overload([](std::uint64_t address) -> std::uint64_t { return MemoryLib::read_long(address, false); }, [](std::uint64_t address, bool absolute) -> std::uint64_t { return MemoryLib::read_long(address, absolute); }));

	_state->set_function("ReadFloat", sol::overload([](std::uint64_t address) -> float { return MemoryLib::read_float(address, false); }, [](std::uint64_t address, bool absolute) -> float { return MemoryLib::read_float(address, absolute); }));

	_state->set_function("ReadBoolean", sol::overload([](std::uint64_t address) -> bool { return MemoryLib::read_bool(address, false); }, [](std::uint64_t address, bool absolute) -> bool { return MemoryLib::read_bool(address, absolute); }));

	_state->set_function("ReadArray", sol::overload([](std::uint64_t address, int length) -> std::vector<std::uint8_t> { return MemoryLib::read_bytes(address, length, false); }, [](std::uint64_t address, int length, bool absolute) -> std::vector<std::uint8_t> { return MemoryLib::read_bytes(address, length, absolute); }));

	_state->set_function("ReadString", sol::overload([](std::uint64_t address, int length) -> std::string { return MemoryLib::read_string(address, length, false); }, [](std::uint64_t address, int length, bool absolute) -> std::string { return MemoryLib::read_string(address, length, absolute); }));

	_state->set_function("WriteByte", sol::overload([](std::uint64_t address, std::uint8_t input) { MemoryLib::write_byte(address, input, false); }, [](std::uint64_t address, std::uint8_t input, bool absolute) { MemoryLib::write_byte(address, input, absolute); }));

	_state->set_function("WriteShort", sol::overload([](std::uint64_t address, std::uint16_t input) { MemoryLib::write_short(address, input, false); }, [](std::uint64_t address, std::uint16_t input, bool absolute) { MemoryLib::write_short(address, input, absolute); }));

	_state->set_function("WriteInt", sol::overload([](std::uint64_t address, std::uint32_t input) { MemoryLib::write_int(address, input, false); }, [](std::uint64_t address, std::uint32_t input, bool absolute) { MemoryLib::write_int(address, input, absolute); }));

	_state->set_function("WriteLong", sol::overload([](std::uint64_t address, std::uint64_t input) { MemoryLib::write_long(address, input, false); }, [](std::uint64_t address, std::uint64_t input, bool absolute) { MemoryLib::write_long(address, input, absolute); }));

	_state->set_function("WriteFloat", sol::overload([](std::uint64_t address, float input) { MemoryLib::write_float(address, input, false); }, [](std::uint64_t address, float input, bool absolute) { MemoryLib::write_float(address, input, absolute); }));

	_state->set_function("WriteBoolean", sol::overload([](std::uint64_t address, bool input) { MemoryLib::write_bool(address, input, false); }, [](std::uint64_t address, bool input, bool absolute) { MemoryLib::write_bool(address, input, absolute); }));

	_state->set_function("WriteArray", sol::overload([](std::uint64_t address, const std::vector<std::uint8_t> &input) { MemoryLib::write_bytes(address, input, false); }, [](std::uint64_t address, const std::vector<std::uint8_t> &input, bool absolute) { MemoryLib::write_bytes(address, input, absolute); }));

	_state->set_function("WriteString", sol::overload([](std::uint64_t address, const std::string &input) { MemoryLib::write_string(address, input, false); }, [](std::uint64_t address, const std::string &input, bool absolute) { MemoryLib::write_string(address, input, absolute); }));

	_state->set_function("WriteExec", [](std::uint64_t address, const std::vector<std::uint8_t> &input) { MemoryLib::write_exec(address, input); });

	_state->set_function("GetPointer", sol::overload(
										   [](std::uint64_t address) -> std::uint64_t {
											   return MemoryLib::get_pointer(address, 0,
																			false); // Offset is defaulted to 0
										   },
										   [](std::uint64_t address, std::uint64_t Offset, bool absolute) -> std::uint64_t { return MemoryLib::get_pointer(address, Offset, absolute); }));

	_state->set_function("ReadByteA", MemoryLib::read_byte_absolute);
	_state->set_function("ReadShortA", MemoryLib::read_short_absolute);
	_state->set_function("ReadIntA", MemoryLib::read_int_absolute);
	_state->set_function("ReadLongA", MemoryLib::read_long_absolute);
	_state->set_function("ReadFloatA", MemoryLib::read_float_absolute);
	_state->set_function("ReadBooleanA", MemoryLib::read_bool_absolute);
	_state->set_function("ReadArrayA", MemoryLib::read_bytes_absolute);
	_state->set_function("ReadStringA", MemoryLib::read_string_absolute);

	_state->set_function("WriteByteA", MemoryLib::write_byte_absolute);
	_state->set_function("WriteShortA", MemoryLib::write_short_absolute);
	_state->set_function("WriteIntA", MemoryLib::write_int_absolute);
	_state->set_function("WriteLongA", MemoryLib::write_long_absolute);
	_state->set_function("WriteFloatA", MemoryLib::write_float_absolute);
	_state->set_function("WriteBooleanA", MemoryLib::write_bool_absolute);
	_state->set_function("WriteArrayA", MemoryLib::write_bytes_absolute);
	_state->set_function("WriteStringA", MemoryLib::write_string_absolute);
	_state->set_function("GetPointerA", MemoryLib::get_pointer_absolute);

	_state->set_function("InitializeRPC", DiscordInstance::initialize_rpc);
	_state->set_function("UpdateDetails", DiscordInstance::update_details);
	_state->set_function("UpdateState", DiscordInstance::update_state);
	_state->set_function("UpdateLImage", DiscordInstance::update_large_image);
	_state->set_function("UpdateSImage", DiscordInstance::update_small_image);

	_state->set_function("ULShift32", [](std::uint32_t base, std::uint32_t shift) { return base << shift; });

	_state->set_function("ConsolePrint", sol::overload(
											 [_state](sol::object text) {
												 HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

												 SetConsoleTextAttribute(_hConsole, 14);
												 std::cout << "[" + _state->globals()["LUA_NAME"].get<std::string>() + "] ";

												 SetConsoleTextAttribute(_hConsole, 7);
												 std::cout << text.as<std::string>() << '\n';
											 },

											 [_state](sol::object text, int message_type) {
												 HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

												 SetConsoleTextAttribute(_hConsole, 14);
												 std::cout << "[" + _state->globals()["LUA_NAME"].get<std::string>() + "] ";

												 switch (message_type) {
												 case 0:
													 SetConsoleTextAttribute(_hConsole, 11);
													 std::cout << "MESSAGE: ";
													 break;
												 case 1:
													 SetConsoleTextAttribute(_hConsole, 10);
													 std::cout << "SUCCESS: ";
													 break;
												 case 2:
													 SetConsoleTextAttribute(_hConsole, 14);
													 std::cout << "WARNING: ";
													 break;
												 case 3:
													 SetConsoleTextAttribute(_hConsole, 12);
													 std::cout << "ERROR: ";
													 break;
												 }

												 SetConsoleTextAttribute(_hConsole, 7);
												 std::cout << text.as<std::string>() << '\n';
											 }));

	_state->set_function("GetHertz", [this]() {
		switch (frame_limit) {
		default: return 60;
		case 8: return 120;
		case 4: return 240;
		}
	});

	_state->set_function("SetHertz", [this](int input) {
		switch (input) {
		default: frame_limit = 16; break;
		case 120: frame_limit = 8; break;
		case 240: frame_limit = 4; break;
		}
	});
}
