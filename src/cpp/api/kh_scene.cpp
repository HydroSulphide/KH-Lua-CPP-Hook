#include "kh_scene.h"
#include "memory_lib.h"

#include <format>

void KHScene::update_loaded_gameobjects() {
	loaded_gameobjects.clear();
	for (size_t i = 0; i < max_loaded_gameobjects; i++) {
		uintptr_t gameobject_pointer = static_cast<uintptr_t>(*(loaded_gameobjects_start_pointer + 8 * i));
		if (gameobject_pointer != 0) {
			KHGameObject gameobject;
			gameobject.entity = reinterpret_cast<Entity *>(gameobject_pointer);
			uintptr_t actor_pointer = MemoryLib::get_4to8_pointer(gameobject.entity->actor_pointer);
			gameobject.actor = reinterpret_cast<Actor *>(actor_pointer);

			loaded_gameobjects.push_back(gameobject);
		}
	}
}

std::string KHScene::to_string() {
	std::string output = "KHScene:\n\tLoaded Gameobjects:\n";
	for (auto &gameobject : loaded_gameobjects) {
		output += std::format("\t\t{}\n", gameobject.to_string());
	}
	return output;
}