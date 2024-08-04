#include "console_lib.h"

void print_message(const std::string &text, MessageType message_type) {
	HANDLE _console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (message_type) {
	case MESSAGE_DEFAULT:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "MESSAGE: ";
		break;
	case MESSAGE_SUCCESS:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_GREEN);
		std::cout << "SUCCESS: ";
		break;
	case MESSAGE_WARNING:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN);
		std::cout << "WARNING: ";
		break;
	case MESSAGE_ERROR:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED);
		std::cout << "ERROR: ";
		break;
	default: 
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
		break;
	}

	SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << text << std::endl;
}

extern "C" __declspec(dllexport) void print_mod_message(const char *text, MessageType message_type) {
	print_message(text, message_type);
}
