#include "lua_exec.h"

#include <memory>
#include <utility>

#include "ConsoleLib.h"
#include "LuaBackend.h"
#include "header_text.h"

namespace fs = std::filesystem;

bool keyPressedF1 = false;
bool keyPressedF2 = false;
bool keyPressedF3 = false;

static std::vector<fs::path> _scriptPaths;

static bool _showConsole = false;
static bool _requestedReset = false;

static std::unique_ptr<LuaBackend> _backend;

void ResetLUA() {
	std::printf("\n");
	ConsoleLib::MessageOutput("Reloading...\n\n", 0);
	_backend = std::make_unique<LuaBackend>(_scriptPaths, MemoryLib::ExecAddress + MemoryLib::BaseAddress);

	if (_backend->loadedScripts.size() == 0)
		ConsoleLib::MessageOutput("No scripts found! Reload halted!\n\n", 3);

	ConsoleLib::MessageOutput("Executing initialization event handlers...\n\n", 0);

	for (auto &_script : _backend->loadedScripts)
		if (_script->initFunction) {
			auto _result = _script->initFunction();

			if (!_result.valid()) {
				sol::error _err = _result;
				ConsoleLib::MessageOutput(_err.what(), 3);
				std::printf("\n\n");
			}
		}

	ConsoleLib::MessageOutput("Reload complete!\n\n", 1);

	_requestedReset = false;
}

int EntryLUA(int ProcessID, HANDLE ProcessH, std::uint64_t TargetAddress, std::vector<fs::path> ScriptPaths) {
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	std::cout << getHeaderText() << '\n';

	ConsoleLib::MessageOutput("Initializing LuaEngine v5.0...\n\n", 0);
	_scriptPaths = std::move(ScriptPaths);

	MemoryLib::ExternProcess(ProcessID, ProcessH, TargetAddress);

	_backend = std::make_unique<LuaBackend>(_scriptPaths, MemoryLib::ExecAddress + TargetAddress);
	_backend->frameLimit = 16;

	if (_backend->loadedScripts.size() == 0) {
		ConsoleLib::MessageOutput("No scripts were found! Initialization halted!\n\n", 3);
		return -1;
	}

	ConsoleLib::MessageOutput("Executing initialization event handlers...\n\n", 0);

	for (auto &_script : _backend->loadedScripts)
		if (_script->initFunction) {
			auto _result = _script->initFunction();

			if (!_result.valid()) {
				sol::error _err = _result;
				ConsoleLib::MessageOutput(_err.what(), 3);
				std::printf("\n\n");
			}
		}

	ConsoleLib::MessageOutput("Initialization complete!\n", 1);
	ConsoleLib::MessageOutput("Press 'F1' to reload all scripts, press 'F2' to toggle the console, press 'F3' to set execution frequency.\n\n", 0);

	return 0;
}

void ExecuteLUA() {
	if (_requestedReset == false) {

		if (GetKeyState(VK_F3) & 0x8000) {
			if (!keyPressedF3) {
				switch (_backend->frameLimit) {
				case 16:
					_backend->frameLimit = 8;
					ConsoleLib::MessageOutput("Frequency set to 120Hz.\n", 0);
					break;
				case 8:
					_backend->frameLimit = 4;
					ConsoleLib::MessageOutput("Frequency set to 240Hz.\n", 0);
					break;
				case 4:
					_backend->frameLimit = 16;
					ConsoleLib::MessageOutput("Frequency set to 60Hz.\n", 0);
					break;
				}
			}
			keyPressedF3 = true;
		} else {
			keyPressedF3 = false;
		}

		if (GetKeyState(VK_F2) & 0x8000) {
			if (!keyPressedF2) {
				if (_showConsole) {
					ShowWindow(GetConsoleWindow(), SW_HIDE);
					_showConsole = false;
				}

				else {
					ShowWindow(GetConsoleWindow(), SW_RESTORE);
					_showConsole = true;
				}
			}
			keyPressedF2 = true;
		} else {
			keyPressedF2 = false;
		}

		if (GetKeyState(VK_F1) & 0x8000) {
			if (!keyPressedF1) {
				_requestedReset = true;
			}
			keyPressedF1 = true;
		} else {
			keyPressedF1 = false;
		}

		for (std::size_t i = 0; i < _backend->loadedScripts.size(); i++) {
			auto &_script = _backend->loadedScripts[i];

			if (_script->frameFunction) {
				auto _result = _script->frameFunction();

				if (!_result.valid()) {
					sol::error _err = _result;
					ConsoleLib::MessageOutput(_err.what(), 3);
					std::printf("\n\n");

					_backend->loadedScripts.erase(_backend->loadedScripts.begin() + i);
				}
			}
		}
	} else
		ResetLUA();
}

bool CheckLUA() {
	auto _int = MemoryLib::ReadInt(0);

	if (_int == 0)
		return false;

	return true;
}

int VersionLUA() {
	return 128;
}
