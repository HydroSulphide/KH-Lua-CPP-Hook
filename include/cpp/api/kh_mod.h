#pragma once

#include <Windows.h>
#include <format>
#include <iostream>
#include <string>

#include "kh_characters.h"

using namespace std;

extern string mod_name;
extern string mod_author;
extern string mod_description;
extern string mod_version;

inline void print(const string &msg) {
	cout << "[" << mod_name << "]: " << msg << endl;
}

inline string get_metadata() {
	return format("[{}]\n\tAuthor: {}\n\tDescription: {}\n\tVersion: {}", mod_name, mod_author, mod_description, mod_version);
}

inline void print_metadata() {
	cout << get_metadata() << endl;
}



extern "C" {
#ifndef KH_MOD_SETUP
// Default on_load implementation
__declspec(dllexport) void __cdecl on_load() {
	print_metadata();
}
#else
// Declaration for custom on_load, to be defined elsewhere
__declspec(dllexport) void __cdecl on_load();
#endif

void __cdecl on_init();
void __cdecl on_frame();

__declspec(dllimport) CharacterStats *get_sora_character_stats();
__declspec(dllimport) CharacterStats *get_donald_character_stats();
__declspec(dllimport) CharacterStats *get_goofy_character_stats();

__declspec(dllimport) FieldStats *get_sora_field_stats();
__declspec(dllimport) FieldStats *get_donald_field_stats();
__declspec(dllimport) FieldStats *get_goofy_field_stats();
}
