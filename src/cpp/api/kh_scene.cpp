#include "kh_scene.h"
#include "memory_lib.h"

#include <format>

void KHScene::update_loaded_gameobjects() {
	loaded_gameobjects.clear();
	for (size_t i = 0; i < 30; i++) {
		uint64_t gameobject_address = *(loaded_gameobjects_start_pointer + i);

		if (gameobject_address != 0) {
			KHGameObject gameobject = KHGameObject(gameobject_address);
			KHGameObject *gameobject_ptr = &gameobject;
			loaded_gameobjects.push_back(gameobject_ptr);

			// print_message_line(gameobject_ptr->to_string());

			if (strcmp(gameobject_ptr->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
				sora = gameobject_ptr;
				print_message_line("Sora loaded!");
			}
		}
	}
}

KHGameObject* KHScene::get_sora() {
	return sora;
}

std::string KHScene::to_string() {
	std::string output = "KHScene:\n\tLoaded Gameobjects:\n";
	for (auto &gameobject : loaded_gameobjects) {
		output += std::format("\t\t{}\n", gameobject.to_string());
	}
	return output;
}