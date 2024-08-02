#pragma once

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "LuaBackend.h"
#include "MemoryLib.h"

void ResetLUA();
int EntryLUA(int ProcessID, HANDLE ProcessH, std::uint64_t TargetAddress, std::vector<std::filesystem::path> ScriptPaths);
void ExecuteLUA();
bool CheckLUA();
int VersionLUA();
