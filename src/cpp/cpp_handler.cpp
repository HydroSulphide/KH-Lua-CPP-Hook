#include "cpp_handler.h"
#include "console_lib.h"
#include "memory_lib.h"

#include <format>

void on_frame_cpp() {
	ConsoleLib::print_message(std::format("Sora Level: {}\n", MemoryLib::read_byte(0x2DE9364)), 0);
}
