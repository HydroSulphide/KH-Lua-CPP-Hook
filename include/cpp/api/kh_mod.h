#pragma once

#define KH_MOD extern "C" __declspec(dllexport) void __cdecl

#include <Windows.h>
#include <format>
#include <iostream>
#include <string>

#include "kh_characters.h"

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

__declspec(dllimport) void print_mod_message(const char *text, MessageType message_type, const char *mod_name);
__declspec(dllimport) void print_mod_message_line(const char *text, MessageType message_type, const char *mod_name);

__declspec(dllimport) CharacterStats *get_sora_character_stats();
__declspec(dllimport) CharacterStats *get_donald_character_stats();
__declspec(dllimport) CharacterStats *get_goofy_character_stats();

__declspec(dllimport) FieldStats *get_sora_field_stats();
__declspec(dllimport) FieldStats *get_donald_field_stats();
__declspec(dllimport) FieldStats *get_goofy_field_stats();
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