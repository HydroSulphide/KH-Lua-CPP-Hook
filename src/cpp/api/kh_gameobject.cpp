#include "kh_gameobject.h"
#include "memory_lib.h"

#include "console_lib.h"

#include <format>

KHGameObject* kh_gameobject_init(uint64_t gameobject_address) {
	KHGameObject *kh_gameobject = new KHGameObject;
	kh_gameobject->gameobject = reinterpret_cast<GameObject *>(gameobject_address);
	uint64_t actor_pointer = MemoryLib::get_4to8_pointer(kh_gameobject->gameobject->actor_pointer);
	kh_gameobject->actor = (actor_pointer != 0xFFFFFFFFFFFFFFFF) ? reinterpret_cast<Actor *>(actor_pointer) : nullptr;
	uint64_t stat_page_pointer = MemoryLib::get_4to8_pointer(kh_gameobject->gameobject->stat_page_pointer);
	kh_gameobject->stat_page = reinterpret_cast<StatPage *>(stat_page_pointer);
	kh_gameobject->party_stat_page = (kh_gameobject->stat_page && kh_gameobject->stat_page->party_stat_page_pointer != 0) ? reinterpret_cast<PartyStatPage *>(kh_gameobject->stat_page->party_stat_page_pointer) : nullptr;
	return kh_gameobject;
}

//KHGameObject::KHGameObject(uint64_t gameobject_address) {
//	gameobject = reinterpret_cast<GameObject *>(gameobject_address);
//	uint64_t actor_pointer = MemoryLib::get_4to8_pointer(gameobject->actor_pointer);
//	actor = (actor_pointer != 0xFFFFFFFFFFFFFFFF) ? reinterpret_cast<Actor *>(actor_pointer) : nullptr;
//	uint64_t stat_page_pointer = MemoryLib::get_4to8_pointer(gameobject->stat_page_pointer);
//	stat_page = reinterpret_cast<StatPage *>(stat_page_pointer);
//	party_stat_page = (stat_page && stat_page->party_stat_page_pointer != 0) ? reinterpret_cast<PartyStatPage *>(stat_page->party_stat_page_pointer) : nullptr;
//
//	if (gameobject_address == 0x7FF7080372A0) {
//		print_message_line(std::format("OBJECT: 0x{:X}", gameobject_address));
//		print_message_line(std::format("ACTOR: 0x{:X}", actor_pointer));
//		print_message_line(std::format("STAT_PAGE: 0x{:X}", stat_page_pointer));
//		print_message_line(std::format("PARTY_STAT_PAGE: 0x{:X}", stat_page->party_stat_page_pointer));
//	}
//}

//std::string KHGameObject::to_string() {
//	if (!actor)
//		return "KHGameObject: No valid actor!";
//	return std::format("KHGameObject:\n\tName: \"{}\"", std::string(actor->name, 16));
//}
