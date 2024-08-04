#pragma once

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "lua_backend.h"
#include "memory_lib.h"

extern std::unique_ptr<LuaBackend> lua_backend;

void reset_lua();
int entry_lua(int process_id, HANDLE process_handle, std::uint64_t target_address, std::vector<std::filesystem::path> script_paths);
void execute_lua();
bool check_lua();
int version_lua();
