#include "discord_instance.h"

void DiscordInstance::initialize_rpc(const char *applicationID) {
	Discord_Initialize(applicationID, NULL, 1, NULL);

	std::memset(&DiscordInstance::presence, 0, sizeof(DiscordInstance::presence));

	auto _curr_time = std::chrono::system_clock::now().time_since_epoch();
	auto _second_cast = std::chrono::duration_cast<std::chrono::seconds>(_curr_time);

	DiscordInstance::presence.startTimestamp = _second_cast.count();
	Discord_UpdatePresence(&DiscordInstance::presence);
}

void DiscordInstance::update_details(const char *input) {
	DiscordInstance::presence.details = input;
	Discord_UpdatePresence(&DiscordInstance::presence);
}

void DiscordInstance::update_state(const char *input) {
	DiscordInstance::presence.state = input;
	Discord_UpdatePresence(&DiscordInstance::presence);
}

void DiscordInstance::update_large_image(const char *key, const char *text) {
	DiscordInstance::presence.largeImageKey = key;
	DiscordInstance::presence.largeImageText = text;
	Discord_UpdatePresence(&DiscordInstance::presence);
}

void DiscordInstance::update_small_image(const char *key, const char *text) {
	DiscordInstance::presence.smallImageKey = key;
	DiscordInstance::presence.smallImageText = text;
	Discord_UpdatePresence(&DiscordInstance::presence);
}
