#pragma once

#define KH_MOD extern "C" __declspec(dllexport) void __cdecl

#include <Windows.h>
#include <format>
#include <iostream>
#include <string>

#include "kh_interface.h"

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

__declspec(dllimport) KHGameObject *get_sora();
__declspec(dllimport) uintptr_t get_object_addr();
__declspec(dllimport) uintptr_t get_actor_addr();
__declspec(dllimport) uintptr_t get_stat_page_addr();
__declspec(dllimport) uintptr_t get_party_stat_page_addr();
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