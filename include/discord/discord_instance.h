#pragma once

#define WIN32_LEAN_AND_MEAN
#include <discord_register.h>
#include <discord_rpc.h>
#include <windows.h>

#include <chrono>

class DiscordInstance {
  public:
	static inline DiscordRichPresence presence;

	static void initialize_rpc(const char *applicationID);

	static void update_details(const char *input);
	static void update_state(const char *input);
	static void update_large_image(const char *key, const char *text);
	static void update_small_image(const char *key, const char *text);
};
