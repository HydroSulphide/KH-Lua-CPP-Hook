#pragma once

#include <cstdint>

void install_event_hook(uintptr_t base_address, uint32_t event_offset, size_t overwritten_instructions_size, void (*custom_logic)(CONTEXT *));