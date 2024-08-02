#pragma once

#include <iostream>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace ConsoleLib {
void MessageOutput(const std::string &Text, int MessageType);
}; // namespace ConsoleLib
