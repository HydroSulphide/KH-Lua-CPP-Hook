#include "kh_interface.h"
#include "console_lib.h"

#include <format>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 30;

uintptr_t loaded_gameobject_addresses[30];


void update_loaded_gameobject_addresses() {
	for (size_t i = 0; i < max_loaded_gameobjects; i++) {
		loaded_gameobject_addresses[i] = *(loaded_gameobjects_start_pointer + i);
	}
}

extern "C" __declspec(dllexport) uintptr_t* get_loaded_gameobject_addresses() {
	return loaded_gameobject_addresses;
}