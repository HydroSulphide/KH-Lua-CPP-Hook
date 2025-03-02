#pragma once

#define KH_MOD extern "C" __declspec(dllexport) void __cdecl

#include <Windows.h>
#include <format>
#include <iostream>
#include <string>

#include "kh_interface.h"
#include "kh_gameobject.h"

using namespace std;

enum MessageType {
	MESSAGE_NONE = -1,
	MESSAGE_DEFAULT = 0,
	MESSAGE_SUCCESS = 1,
	MESSAGE_WARNING = 2,
	MESSAGE_ERROR = 3
};

extern string mod_name;
extern string mod_author;
extern string mod_description;
extern string mod_version;

extern "C" {

void __cdecl on_init();
void __cdecl on_frame();
void __cdecl on_get_reward(DWORD64 reward_id);
void __cdecl on_get_hit();

__declspec(dllimport) void print_mod_message(const char *text, MessageType message_type, const char *mod_name);
__declspec(dllimport) void print_mod_message_line(const char *text, MessageType message_type, const char *mod_name);

__declspec(dllimport) KHGameObject *kh_gameobject_init(uint64_t gameobject_address);
__declspec(dllimport) uintptr_t *get_loaded_gameobject_addresses();
}

inline std::vector<KHGameObject *> &get_loaded_gameobjects() {
	static std::vector<KHGameObject *> loaded_gameobjects; // Persistent storage
	return loaded_gameobjects;
}

inline KHGameObject* &get_sora() {
	static KHGameObject *sora = nullptr;

	return sora;
}

inline void update_loaded_gameobjects() {
	KHGameObject *&sora_ref = get_sora();
	auto &game_objects = get_loaded_gameobjects(); 
	game_objects.clear();
	uintptr_t *game_object_addresses = get_loaded_gameobject_addresses();
	if (!game_object_addresses) {
		return;
	}

	for (size_t i = 0; i < 30; i++) {
		if (game_object_addresses[i] != 0) {
			KHGameObject *gameobject_ptr = kh_gameobject_init(game_object_addresses[i]);
			game_objects.push_back(gameobject_ptr);

			if (gameobject_ptr->actor && (strcmp(gameobject_ptr->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0)) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
				sora_ref = gameobject_ptr;
			}
		}
	}
}

inline void print(const string &text, MessageType message_type = MESSAGE_NONE) {
	print_mod_message(text.c_str(), message_type, mod_name.c_str());
}

inline void print_line(const string &text, MessageType message_type = MESSAGE_NONE) {
	print_mod_message_line(text.c_str(), message_type, mod_name.c_str());
}

inline string get_metadata() {
	return format("\n\tAuthor: {}\n\tDescription: {}\n\tVersion: {}", mod_author, mod_description, mod_version);
}

inline void print_metadata() {
	print_mod_message_line(get_metadata().c_str(), MESSAGE_NONE, mod_name.c_str());
}

KH_MOD on_load() {
	print_metadata();
}