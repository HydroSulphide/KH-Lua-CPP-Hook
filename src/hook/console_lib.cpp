#include "console_lib.h"

void ConsoleLib::print_message(const std::string &text, int message_type) {
	HANDLE _console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (message_type) {
	case 0:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "MESSAGE: ";
		break;
	case 1:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_GREEN);
		std::cout << "SUCCESS: ";
		break;
	case 2:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN);
		std::cout << "WARNING: ";
		break;
	case 3:
		SetConsoleTextAttribute(_console_handle, FOREGROUND_RED);
		std::cout << "ERROR: ";
		break;
	default: SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	}

	SetConsoleTextAttribute(_console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << text;
}
