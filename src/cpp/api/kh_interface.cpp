#include "kh_interface.h"
#include "console_lib.h"

#include <format>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 30;

std::vector<KHGameObject*> loaded_gameobjects;
KHGameObject *sora;


void update_loaded_gameobject_addresses() {
	loaded_gameobjects.clear();

	for (size_t i = 0; i < 30; i++) {
		uint64_t gameobject_address = *(loaded_gameobjects_start_pointer + i);
		if (gameobject_address != 0) {
			KHGameObject *gameobject_ptr = kh_gameobject_init(gameobject_address);
			loaded_gameobjects.push_back(gameobject_ptr);

			if (gameobject_ptr->actor && (strcmp(gameobject_ptr->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0)) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
				sora = gameobject_ptr;
			}
		}
	}
}

extern "C" __declspec(dllexport) KHGameObject **get_loaded_gameobjects(size_t *count) {
	*count = loaded_gameobjects.size();
	return loaded_gameobjects.data();
}

extern "C" __declspec(dllexport) KHGameObject* __cdecl get_sora() {
	return sora;
}