#include "LuaBackend.h"

#include <crcpp/CRC.h>

#include <string>
#include <utility>

namespace fs = std::filesystem;

LuaBackend::LuaBackend(const std::vector<fs::path> &ScriptPaths, std::uint64_t BaseInput) {
	frameLimit = 16;
	LoadScripts(ScriptPaths, BaseInput);
}

int LuaBackend::ExceptionHandle(lua_State *luaState, sol::optional<const std::exception &> thrownException, sol::string_view description) {
	(void)description;

	const std::exception _ex = *thrownException;
	ConsoleLib::MessageOutput(std::string{_ex.what()} + "\n", 3);

	return sol::stack::push(luaState, _ex.what());
}

void LuaBackend::LoadScripts(const std::vector<fs::path> &ScriptPaths, std::uint64_t BaseInput) {
	loadedScripts.clear();

	for (auto scriptsDir : ScriptPaths) {
		if (!fs::is_directory(scriptsDir)) {
			continue;
		}

		for (auto _path : fs::directory_iterator(scriptsDir)) {
			auto _script = std::make_unique<LuaScript>();

			// clang-format off
            _script->luaState.open_libraries(
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

			_script->luaState.set_exception_handler(&ExceptionHandle);

			SetFunctions(&_script->luaState);

			fs::path _luaPath = scriptsDir / L"io_packages" / L"?.lua";
			fs::path _dllPath = scriptsDir / L"io_packages" / L"?.dll";

			_script->luaState["package"]["path"] = _luaPath.string();
			_script->luaState["package"]["cpath"] = _dllPath.string();

			fs::path _loadPath = scriptsDir / L"io_load";

			_script->luaState["LOAD_PATH"] = _loadPath.string();
			_script->luaState["SCRIPT_PATH"] = scriptsDir.string();
			_script->luaState["CHEATS_PATH"] = "NOT_AVAILABLE";

			fs::path _pathFull = MemoryLib::PName;
			auto _pathExe = _pathFull.filename().string();

			_script->luaState["ENGINE_VERSION"] = 5;
			_script->luaState["ENGINE_TYPE"] = "BACKEND";
			_script->luaState["GAME_ID"] = CRC::Calculate(_pathExe.c_str(), _pathExe.length(), CRC::CRC_32());
			_script->luaState["BASE_ADDR"] = BaseInput;

			const auto _filePath = _path.path();
			const auto _filePathStr = _filePath.string();

			if (_filePath.extension() == ".lua") {
				_script->luaState["LUA_NAME"] = _filePath.filename().string();

				ConsoleLib::MessageOutput("Found script: \"" + _filePathStr + "\" Initializing...\n", 0);

				auto _result = _script->luaState.script_file(_filePathStr, &sol::script_pass_on_error);

				_script->initFunction = _script->luaState["_OnInit"];
				_script->frameFunction = _script->luaState["_OnFrame"];

				if (_result.valid()) {
					if (!_script->initFunction && !_script->frameFunction) {
						ConsoleLib::MessageOutput("No event handlers exist or all of them have errors.\n", 3);
						ConsoleLib::MessageOutput("Initialization of this script cannot continue...\n", 3);
						return;
					}

					if (!_script->initFunction)
						ConsoleLib::MessageOutput("The event handler for initialization either has errors or does not exist.\n", 2);

					if (!_script->frameFunction)
						ConsoleLib::MessageOutput("The event handler for framedraw either has errors or does not exist.\n", 2);

					ConsoleLib::MessageOutput("Initialization of this script was successful!\n\n", 1);

					loadedScripts.push_back(std::move(_script));
				} else {
					sol::error err = _result;
					ConsoleLib::MessageOutput(std::string{err.what()} + "\n", 3);
					ConsoleLib::MessageOutput("Initialization of this script was aborted.\n", 3);
				}
			}
		}
	}
}

void LuaBackend::SetFunctions(LuaState *_state) {
	_state->set_function("ReadByte", sol::overload([](std::uint64_t Address) -> std::uint8_t { return MemoryLib::ReadByte(Address, false); }, [](std::uint64_t Address, bool absolute) -> std::uint8_t { return MemoryLib::ReadByte(Address, absolute); }));

	_state->set_function("ReadShort", sol::overload([](std::uint64_t Address) -> std::uint16_t { return MemoryLib::ReadShort(Address, false); }, [](std::uint64_t Address, bool absolute) -> std::uint16_t { return MemoryLib::ReadShort(Address, absolute); }));

	_state->set_function("ReadInt", sol::overload([](std::uint64_t Address) -> std::uint32_t { return MemoryLib::ReadInt(Address, false); }, [](std::uint64_t Address, bool absolute) -> std::uint32_t { return MemoryLib::ReadInt(Address, absolute); }));

	_state->set_function("ReadLong", sol::overload([](std::uint64_t Address) -> std::uint64_t { return MemoryLib::ReadLong(Address, false); }, [](std::uint64_t Address, bool absolute) -> std::uint64_t { return MemoryLib::ReadLong(Address, absolute); }));

	_state->set_function("ReadFloat", sol::overload([](std::uint64_t Address) -> float { return MemoryLib::ReadFloat(Address, false); }, [](std::uint64_t Address, bool absolute) -> float { return MemoryLib::ReadFloat(Address, absolute); }));

	_state->set_function("ReadBoolean", sol::overload([](std::uint64_t Address) -> bool { return MemoryLib::ReadBool(Address, false); }, [](std::uint64_t Address, bool absolute) -> bool { return MemoryLib::ReadBool(Address, absolute); }));

	_state->set_function("ReadArray", sol::overload([](std::uint64_t Address, int Length) -> std::vector<std::uint8_t> { return MemoryLib::ReadBytes(Address, Length, false); }, [](std::uint64_t Address, int Length, bool absolute) -> std::vector<std::uint8_t> { return MemoryLib::ReadBytes(Address, Length, absolute); }));

	_state->set_function("ReadString", sol::overload([](std::uint64_t Address, int Length) -> std::string { return MemoryLib::ReadString(Address, Length, false); }, [](std::uint64_t Address, int Length, bool absolute) -> std::string { return MemoryLib::ReadString(Address, Length, absolute); }));

	_state->set_function("WriteByte", sol::overload([](std::uint64_t Address, std::uint8_t Input) { MemoryLib::WriteByte(Address, Input, false); }, [](std::uint64_t Address, std::uint8_t Input, bool absolute) { MemoryLib::WriteByte(Address, Input, absolute); }));

	_state->set_function("WriteShort", sol::overload([](std::uint64_t Address, std::uint16_t Input) { MemoryLib::WriteShort(Address, Input, false); }, [](std::uint64_t Address, std::uint16_t Input, bool absolute) { MemoryLib::WriteShort(Address, Input, absolute); }));

	_state->set_function("WriteInt", sol::overload([](std::uint64_t Address, std::uint32_t Input) { MemoryLib::WriteInt(Address, Input, false); }, [](std::uint64_t Address, std::uint32_t Input, bool absolute) { MemoryLib::WriteInt(Address, Input, absolute); }));

	_state->set_function("WriteLong", sol::overload([](std::uint64_t Address, std::uint64_t Input) { MemoryLib::WriteLong(Address, Input, false); }, [](std::uint64_t Address, std::uint64_t Input, bool absolute) { MemoryLib::WriteLong(Address, Input, absolute); }));

	_state->set_function("WriteFloat", sol::overload([](std::uint64_t Address, float Input) { MemoryLib::WriteFloat(Address, Input, false); }, [](std::uint64_t Address, float Input, bool absolute) { MemoryLib::WriteFloat(Address, Input, absolute); }));

	_state->set_function("WriteBoolean", sol::overload([](std::uint64_t Address, bool Input) { MemoryLib::WriteBool(Address, Input, false); }, [](std::uint64_t Address, bool Input, bool absolute) { MemoryLib::WriteBool(Address, Input, absolute); }));

	_state->set_function("WriteArray", sol::overload([](std::uint64_t Address, const std::vector<std::uint8_t> &Input) { MemoryLib::WriteBytes(Address, Input, false); }, [](std::uint64_t Address, const std::vector<std::uint8_t> &Input, bool absolute) { MemoryLib::WriteBytes(Address, Input, absolute); }));

	_state->set_function("WriteString", sol::overload([](std::uint64_t Address, const std::string &Input) { MemoryLib::WriteString(Address, Input, false); }, [](std::uint64_t Address, const std::string &Input, bool absolute) { MemoryLib::WriteString(Address, Input, absolute); }));

	_state->set_function("WriteExec", [](std::uint64_t Address, const std::vector<std::uint8_t> &Input) { MemoryLib::WriteExec(Address, Input); });

	_state->set_function("GetPointer", sol::overload(
										   [](std::uint64_t Address) -> std::uint64_t {
											   return MemoryLib::GetPointer(Address, 0,
																			false); // Offset is defaulted to 0
										   },
										   [](std::uint64_t Address, std::uint64_t Offset, bool absolute) -> std::uint64_t { return MemoryLib::GetPointer(Address, Offset, absolute); }));

	_state->set_function("ReadByteA", MemoryLib::ReadByteAbsolute);
	_state->set_function("ReadShortA", MemoryLib::ReadShortAbsolute);
	_state->set_function("ReadIntA", MemoryLib::ReadIntAbsolute);
	_state->set_function("ReadLongA", MemoryLib::ReadLongAbsolute);
	_state->set_function("ReadFloatA", MemoryLib::ReadFloatAbsolute);
	_state->set_function("ReadBooleanA", MemoryLib::ReadBoolAbsolute);
	_state->set_function("ReadArrayA", MemoryLib::ReadBytesAbsolute);
	_state->set_function("ReadStringA", MemoryLib::ReadStringAbsolute);

	_state->set_function("WriteByteA", MemoryLib::WriteByteAbsolute);
	_state->set_function("WriteShortA", MemoryLib::WriteShortAbsolute);
	_state->set_function("WriteIntA", MemoryLib::WriteIntAbsolute);
	_state->set_function("WriteLongA", MemoryLib::WriteLongAbsolute);
	_state->set_function("WriteFloatA", MemoryLib::WriteFloatAbsolute);
	_state->set_function("WriteBooleanA", MemoryLib::WriteBoolAbsolute);
	_state->set_function("WriteArrayA", MemoryLib::WriteBytesAbsolute);
	_state->set_function("WriteStringA", MemoryLib::WriteStringAbsolute);
	_state->set_function("GetPointerA", MemoryLib::GetPointerAbsolute);

	_state->set_function("InitializeRPC", DCInstance::InitializeRPC);
	_state->set_function("UpdateDetails", DCInstance::UpdateDetails);
	_state->set_function("UpdateState", DCInstance::UpdateState);
	_state->set_function("UpdateLImage", DCInstance::UpdateLImage);
	_state->set_function("UpdateSImage", DCInstance::UpdateSImage);

	_state->set_function("ULShift32", [](std::uint32_t base, std::uint32_t shift) { return base << shift; });

	_state->set_function("ConsolePrint", sol::overload(
											 [_state](sol::object Text) {
												 HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

												 SetConsoleTextAttribute(_hConsole, 14);
												 std::cout << "[" + _state->globals()["LUA_NAME"].get<std::string>() + "] ";

												 SetConsoleTextAttribute(_hConsole, 7);
												 std::cout << Text.as<std::string>() << '\n';
											 },

											 [_state](sol::object Text, int MessageType) {
												 HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

												 SetConsoleTextAttribute(_hConsole, 14);
												 std::cout << "[" + _state->globals()["LUA_NAME"].get<std::string>() + "] ";

												 switch (MessageType) {
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
												 std::cout << Text.as<std::string>() << '\n';
											 }));

	_state->set_function("GetHertz", [this]() {
		switch (frameLimit) {
		default: return 60;
		case 8: return 120;
		case 4: return 240;
		}
	});

	_state->set_function("SetHertz", [this](int Input) {
		switch (Input) {
		default: frameLimit = 16; break;
		case 120: frameLimit = 8; break;
		case 240: frameLimit = 4; break;
		}
	});
}
