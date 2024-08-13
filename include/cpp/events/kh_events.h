#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void on_get_reward(CONTEXT *ctx);
void on_get_hit([[maybe_unused]] CONTEXT *ctx);