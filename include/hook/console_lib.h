#pragma once

#include <iostream>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

enum MessageType {
	MESSAGE_NONE = -1,
	MESSAGE_DEFAULT = 0,
	MESSAGE_SUCCESS = 1,
	MESSAGE_WARNING = 2,
	MESSAGE_ERROR = 3
};


void print_message(const std::string &text, MessageType message_type = MESSAGE_NONE, const std::string &mod_name = "");
void print_message_line(const std::string &text, MessageType message_type = MESSAGE_NONE, const std::string &mod_name = "");