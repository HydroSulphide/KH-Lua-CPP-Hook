#include "cpp_handler.h"
#include "console_lib.h"
#include "kh_characters.h"

#include <format>

#include <toml++/toml.h>

bool api_init(uintptr_t base_address, const std::filesystem::path &path) {
	auto offsets = toml::parse_file(path.u8string());

	uintptr_t sora_character_stats_address = offsets["character_stats"]["sora"].value_or(0);
	uintptr_t donald_character_stats_address = offsets["character_stats"]["donald"].value_or(0);
	uintptr_t goofy_character_stats_address = offsets["character_stats"]["goofy"].value_or(0);

	uintptr_t sora_field_stats_address = offsets["field_stats"]["sora"].value_or(0);
	uintptr_t donald_field_stats_address = offsets["field_stats"]["donald"].value_or(0);
	uintptr_t goofy_field_stats_address = offsets["field_stats"]["goofy"].value_or(0);

	character_stats_init(base_address, sora_character_stats_address, donald_character_stats_address, goofy_character_stats_address);
	field_stats_init(base_address, sora_field_stats_address, donald_field_stats_address, goofy_field_stats_address);

	return true;
}

void on_frame_cpp() {
	ConsoleLib::print_message(std::format("Sora Level: {}\n", sora_character_stats->level), MessageType::MESSAGE_NONE);
}
