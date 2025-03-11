#include "kh_interface.h"
#include "kh_gameobject.h"
#include "kh_party.h"
#include "kh_inventory.h"
#include "console_lib.h"

#include <format>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 35;

std::vector<KHGameObject*> loaded_gameobjects;
KHGameObject *sora;

KHParty *party;
KHInventory *inventory;

void update_loaded_gameobject_addresses() {
	for (KHGameObject *obj : loaded_gameobjects)
		delete obj;
	loaded_gameobjects.clear();

	for (size_t i = 0; i < max_loaded_gameobjects; i++) {
		uint64_t gameobject_address = *(loaded_gameobjects_start_pointer + i);
		if (gameobject_address != 0) {
			KHGameObject *gameobject_ptr = init_kh_gameobject(gameobject_address);
			loaded_gameobjects.push_back(gameobject_ptr);

			if (gameobject_ptr->actor && (strcmp(gameobject_ptr->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0)) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
				sora = gameobject_ptr;
			}
		}
	}
}

void init_kh_inventory(uint64_t item_stock_address, uint64_t gummi_stock_address, uint64_t munny_address) {
	delete inventory;
	inventory = new KHInventory{
		reinterpret_cast<KHItemStock *>(item_stock_address),
		reinterpret_cast<KHGummiStock *>(gummi_stock_address),
		reinterpret_cast<uint32_t *>(munny_address),
	};
}

extern "C" __declspec(dllexport) KHGameObject **get_loaded_gameobjects(size_t *count) {
	*count = loaded_gameobjects.size();
	return loaded_gameobjects.data();
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_sora() {
	return sora;
}

extern "C" __declspec(dllexport) KHParty *__cdecl get_party() {
	return party;
}

extern "C" __declspec(dllexport) KHInventory *__cdecl get_inventory() {
	return inventory;
}