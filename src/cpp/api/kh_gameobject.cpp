#include "kh_gameobject.h"

#include <format>

std::string KHGameObject::to_string() {
	return std::format("KHGameObject:\n\tName: {}", actor->name);
}
