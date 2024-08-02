#include "CPPHandler.h"
#include "ConsoleLib.h"
#include "MemoryLib.h"

#include <format>

void OnFrameCPP() {
	ConsoleLib::MessageOutput(std::format("Sora Level: {}\n", MemoryLib::ReadByte(0x2DE9364)), 0);
}
