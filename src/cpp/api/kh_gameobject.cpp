#include "kh_gameobject.h"
#include "memory_lib.h"

#include "console_lib.h"

#include <format>

KHGameObject *init_kh_gameobject(uint64_t gameobject_address) {
	KHGameObject *kh_gameobject = new KHGameObject;
	kh_gameobject->object = reinterpret_cast<KHObject *>(gameobject_address);
	uint64_t actor_pointer = MemoryLib::get_4to8_pointer(kh_gameobject->object->model_pointer);
	kh_gameobject->model = (actor_pointer != 0xFFFFFFFFFFFFFFFF) ? reinterpret_cast<KHModel *>(actor_pointer) : nullptr;
	uint64_t stat_page_pointer = MemoryLib::get_4to8_pointer(kh_gameobject->object->battle_stats_pointer);
	kh_gameobject->battle_stats = reinterpret_cast<KHBattleStats *>(stat_page_pointer);
	kh_gameobject->attributes = (kh_gameobject->battle_stats && kh_gameobject->battle_stats->attributes_pointer != 0) ? reinterpret_cast<KHAttributes *>(kh_gameobject->battle_stats->attributes_pointer) : nullptr;
	return kh_gameobject;
}
