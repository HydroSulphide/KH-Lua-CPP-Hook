#pragma once

#define WIN32_LEAN_AND_MEAN
#include <discord_register.h>
#include <discord_rpc.h>
#include <windows.h>

#include <chrono>

class DCInstance {
  public:
	static inline DiscordRichPresence Presence;

	static void InitializeRPC(const char *applicationID);

	static void UpdateDetails(const char *input);
	static void UpdateState(const char *input);
	static void UpdateLImage(const char *key, const char *text);
	static void UpdateSImage(const char *key, const char *text);
};
