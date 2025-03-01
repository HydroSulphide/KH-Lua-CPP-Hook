#pragma once

#include "kh_gameobject.h"

#include <vector>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 30;

class KHScene {
  public:
	std::vector<KHGameObject*> loaded_gameobjects;

	void update_loaded_gameobjects();
	std::string to_string();

	KHGameObject *get_sora();

	KHScene() : loaded_gameobjects(std::vector<KHGameObject *>{}), sora(nullptr) {}

  private:
	KHGameObject *sora;
	uint64 sora_address;
};