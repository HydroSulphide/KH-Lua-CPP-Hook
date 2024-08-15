#include "kh_gameobject.h"

#include <format>

std::string KHGameObject::to_string() {
	if (!actor)
		return "KHGameObject: No valid actor!";
	return std::format("KHGameObject:\n\tName: {}", std::string(actor->name, 16));
}
