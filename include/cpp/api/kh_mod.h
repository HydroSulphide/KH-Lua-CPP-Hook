#pragma once

#define KH_MOD extern "C" __declspec(dllexport) void __cdecl

#include <Windows.h>
#include <format>
#include <iostream>
#include <string>

#include "kh_interface.h"
#include "kh_gameobject.h"
#include "kh_inventory.h"
#include "kh_party.h"

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

__declspec(dllexport) void __cdecl on_init();
__declspec(dllexport) void __cdecl on_frame();
__declspec(dllexport) void __cdecl on_get_reward(DWORD64 reward_id);
__declspec(dllexport) void __cdecl on_get_hit(KHGameObject *gameobject);
__declspec(dllexport) void __cdecl on_attack(KHGameObject *gameobject);

__declspec(dllimport) void print_mod_message(const char *text, MessageType message_type, const char *mod_name);
__declspec(dllimport) void print_mod_message_line(const char *text, MessageType message_type, const char *mod_name);

__declspec(dllimport) KHGameObject **get_loaded_gameobjects(size_t *count);

__declspec(dllimport) KHParty *get_party();

__declspec(dllimport) KHGameObject *get_sora();
__declspec(dllimport) KHGameObject *get_donald();
__declspec(dllimport) KHGameObject *get_goofy();
__declspec(dllimport) KHGameObject *get_tarzan();
__declspec(dllimport) KHGameObject *get_aladdin();
__declspec(dllimport) KHGameObject *get_ariel();
__declspec(dllimport) KHGameObject *get_jack();
__declspec(dllimport) KHGameObject *get_peter_pan();
__declspec(dllimport) KHGameObject *get_beast();

__declspec(dllimport) KHAttributes *get_sora_attributes();
__declspec(dllimport) KHAttributes *get_donald_attributes();
__declspec(dllimport) KHAttributes *get_goofy_attributes();
__declspec(dllimport) KHAttributes *get_tarzan_attributes();
__declspec(dllimport) KHAttributes *get_aladdin_attributes();
__declspec(dllimport) KHAttributes *get_ariel_attributes();
__declspec(dllimport) KHAttributes *get_jack_attributes();
__declspec(dllimport) KHAttributes *get_peter_pan_attributes();
__declspec(dllimport) KHAttributes *get_beast_attributes();

__declspec(dllimport) KHInventory *get_inventory();
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