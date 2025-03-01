#pragma once

#include "kh_gameobject.h"

#include <vector>

extern uintptr_t *loaded_gameobjects_start_pointer;
extern size_t max_loaded_gameobjects;
extern std::vector<KHGameObject *> loaded_gameobjects;

extern KHGameObject *sora;

extern uintptr_t object_addr;
extern uintptr_t actor_addr;
extern uintptr_t stat_page_addr;
extern uintptr_t party_stat_page_addr;

void update_loaded_gameobjects();