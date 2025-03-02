#pragma once

#include "kh_gameobject.h"

#include <vector>

extern uintptr_t *loaded_gameobjects_start_pointer;
extern size_t max_loaded_gameobjects;

extern uintptr_t loaded_gameobject_addresses[30];

void update_loaded_gameobject_addresses();