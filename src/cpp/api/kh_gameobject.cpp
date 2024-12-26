#include "kh_gameobject.h"
#include "memory_lib.h"

#include <format>

KHGameObject::KHGameObject(uint64_t gameobject_address) {
	entity = reinterpret_cast<Entity *>(gameobject_address);
	uint64_t actor_pointer = MemoryLib::get_4to8_pointer(entity->actor_pointer);
	actor = (actor_pointer != 0xFFFFFFFFFFFFFFFF) ? reinterpret_cast<Actor *>(actor_pointer) : nullptr;
	uint64_t stat_page_pointer = MemoryLib::get_4to8_pointer(entity->stat_page_pointer);
	stat_page = reinterpret_cast<StatPage *>(stat_page_pointer);
	party_stat_page = (stat_page && stat_page->party_stat_page_pointer != 0) ? reinterpret_cast<PartyStatPage *>(stat_page->party_stat_page_pointer) : nullptr;
}

std::string KHGameObject::to_string() {
	if (!actor)
		return "KHGameObject: No valid actor!";
	return std::format("KHGameObject:\n\tName: {}", std::string(actor->name, 16));
}
