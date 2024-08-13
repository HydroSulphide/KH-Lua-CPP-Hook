#include "kh_events.h"
#include "console_lib.h"

#include <format>

void on_get_reward(CONTEXT *ctx) {
	//current_scene.update_loaded_gameobjects();
	//print_message_line(current_scene.to_string(), MESSAGE_NONE);
	print_message_line(std::format("on_get_reward(): treasure_id: 0x{:X}", ctx->Rcx), MESSAGE_NONE);
}

void on_get_hit([[maybe_unused]] CONTEXT *ctx) {
	print_message_line("on_get_hit()", MESSAGE_NONE);
}
