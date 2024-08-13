#pragma once

#include "kh_gameobject.h"

#include <vector>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 30;

class KHScene {
  public:
	std::vector<KHGameObject> loaded_gameobjects;

	void update_loaded_gameobjects();
	std::string to_string();
};

KHScene current_scene;