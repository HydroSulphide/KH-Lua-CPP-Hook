#ifndef LUABACKEND
#define LUABACKEND

#include <filesystem>
#include <iostream>
#include <memory>
#include <sol/sol.hpp>

#include "console_lib.h"
#include "discord_instance.h"
#include "memory_lib.h"

using LuaState = sol::state;
using LuaFunction = sol::safe_function;

class LuaBackend {
  public:
	struct LuaScript {
		LuaState lua_state;
		LuaFunction init_function;
		LuaFunction frame_function;
	};

	std::vector<std::unique_ptr<LuaScript>> loaded_scripts;
	int frame_limit;

	LuaBackend(const std::vector<std::filesystem::path> &script_paths, std::uint64_t base_input);

	static int exception_handle(lua_State *lua_state, sol::optional<const std::exception &> thrown_exception, sol::string_view description);

	void load_scripts(const std::vector<std::filesystem::path> &script_paths, std::uint64_t base_input);
	void set_functions(LuaState *_state);
};

#endif
