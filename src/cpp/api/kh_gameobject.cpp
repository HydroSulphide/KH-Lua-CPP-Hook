#include "kh_gameobject.h"
#include "memory_lib.h"

#include "console_lib.h"

#include <format>

KHGameObject *init_kh_gameobject(uint64_t gameobject_address) {
	KHGameObject *kh_gameobject = new KHGameObject;
	kh_gameobject->gameobject = reinterpret_cast<GameObject *>(gameobject_address);
	uint64_t actor_pointer = MemoryLib::get_4to8_pointer(kh_gameobject->gameobject->actor_pointer);
	kh_gameobject->actor = (actor_pointer != 0xFFFFFFFFFFFFFFFF) ? reinterpret_cast<Actor *>(actor_pointer) : nullptr;
	uint64_t stat_page_pointer = MemoryLib::get_4to8_pointer(kh_gameobject->gameobject->stat_page_pointer);
	kh_gameobject->stat_page = reinterpret_cast<StatPage *>(stat_page_pointer);
	kh_gameobject->party_stat_page = (kh_gameobject->stat_page && kh_gameobject->stat_page->party_stat_page_pointer != 0) ? reinterpret_cast<PartyStatPage *>(kh_gameobject->stat_page->party_stat_page_pointer) : nullptr;
	return kh_gameobject;
}
