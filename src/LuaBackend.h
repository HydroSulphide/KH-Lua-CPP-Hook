#ifndef LUABACKEND
#define LUABACKEND

#include <filesystem>
#include <iostream>
#include <memory>
#include <sol/sol.hpp>

#include "ConsoleLib.h"
#include "DCInstance.h"
#include "MemoryLib.h"

using LuaState = sol::state;
using LuaFunction = sol::safe_function;

class LuaBackend {
  public:
	struct LuaScript {
		LuaState luaState;
		LuaFunction initFunction;
		LuaFunction frameFunction;
	};

	std::vector<std::unique_ptr<LuaScript>> loadedScripts;
	int frameLimit;

	LuaBackend(const std::vector<std::filesystem::path> &ScriptPaths, std::uint64_t BaseInput);

	static int ExceptionHandle(lua_State *luaState, sol::optional<const std::exception &> thrownException, sol::string_view description);

	void LoadScripts(const std::vector<std::filesystem::path> &ScriptPaths, std::uint64_t BaseInput);
	void SetFunctions(LuaState *_state);
};

#endif
