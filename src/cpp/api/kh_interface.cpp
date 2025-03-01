#include "kh_interface.h"
#include "console_lib.h"

#include <format>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 30;
std::vector<KHGameObject *> loaded_gameobjects;

KHGameObject *sora = nullptr;

uintptr_t object_addr = 0;
uintptr_t actor_addr = 0;
uintptr_t stat_page_addr = 0;
uintptr_t party_stat_page_addr = 0;

void update_loaded_gameobjects() {
	loaded_gameobjects.clear();
	for (size_t i = 0; i < 30; i++) {
		uint64_t gameobject_address = *(loaded_gameobjects_start_pointer + i);


		if (gameobject_address != 0) {
			//print_message_line(std::format("OBJECT {:d}: 0x{:X}", i, gameobject_address));
			//KHGameObject gameobject = KHGameObject(gameobject_address);
			//KHGameObject *gameobject_ptr = &gameobject;
			KHGameObject *gameobject_ptr = kh_gameobject_init(gameobject_address);
			loaded_gameobjects.push_back(gameobject_ptr);

			//print_message_line(gameobject_ptr->to_string());

			if (strcmp(gameobject_ptr->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
				std::string addressStr = std::format("Gameobject: 0x{:X}", reinterpret_cast<uintptr_t>(gameobject_ptr->gameobject));
				print_message_line(addressStr);

				addressStr = std::format("Actor: 0x{:X}", reinterpret_cast<uintptr_t>(gameobject_ptr->actor));
				print_message_line(addressStr);

				addressStr = std::format("Stat Page: 0x{:X}", reinterpret_cast<uintptr_t>(gameobject_ptr->stat_page));
				print_message_line(addressStr);

				addressStr = std::format("Party Stat Page: 0x{:X}", reinterpret_cast<uintptr_t>(gameobject_ptr->party_stat_page));
				print_message_line(addressStr);

				sora = gameobject_ptr;
				object_addr = gameobject_address;
				actor_addr = reinterpret_cast<uintptr_t>(gameobject_ptr->actor);
				stat_page_addr = reinterpret_cast<uintptr_t>(gameobject_ptr->stat_page);
				party_stat_page_addr = reinterpret_cast<uintptr_t>(gameobject_ptr->party_stat_page);
			}
		}
	}
}

extern "C" __declspec(dllexport) KHGameObject *get_sora() {
	return sora;
}

extern "C" __declspec(dllexport) uintptr_t get_object_addr() {
	return object_addr;
}
extern "C" __declspec(dllexport) uintptr_t get_actor_addr() {
	return actor_addr;
}
extern "C" __declspec(dllexport) uintptr_t get_stat_page_addr() {
	return stat_page_addr;
}
extern "C" __declspec(dllexport) uintptr_t get_party_stat_page_addr() {
	return party_stat_page_addr;
}