#pragma once

#include <iostream>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace ConsoleLib {
void print_message(const std::string &text, int message_type);
}; // namespace ConsoleLib
