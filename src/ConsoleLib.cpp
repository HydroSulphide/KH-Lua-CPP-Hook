#include "ConsoleLib.h"

void ConsoleLib::MessageOutput(const std::string &Text, int MessageType) {
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (MessageType) {
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
	std::cout << Text;
}
