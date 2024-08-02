#include "console_lib.h"

void ConsoleLib::print_message(const std::string &text, int message_type) {
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (message_type) {
	case 0:
		SetConsoleTextAttribute(_hConsole, 11);
		std::cout << "MESSAGE: ";
		break;
	case 1:
		SetConsoleTextAttribute(_hConsole, 10);
		std::cout << "SUCCESS: ";
		break;
	case 2:
		SetConsoleTextAttribute(_hConsole, 14);
		std::cout << "WARNING: ";
		break;
	case 3:
		SetConsoleTextAttribute(_hConsole, 12);
		std::cout << "ERROR: ";
		break;
	}

	SetConsoleTextAttribute(_hConsole, 7);
	std::cout << text;
}
