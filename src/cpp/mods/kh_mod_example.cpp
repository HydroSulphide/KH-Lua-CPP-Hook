#include "kh_mod.h"

// Define metadata variables
string mod_name = "Example Mod";
string mod_author = "HydroSulphide";
string mod_description = "This is a description of Example Mod.";
string mod_version = "1.0.0";

KH_MOD on_init() {
	print_line("on_init()");
}

KH_MOD on_frame() {
	KHGameObject *sora = get_sora();

	if (sora && sora->party_stat_page) {
		print_line(std::format("SORA HP: {:d}", sora->party_stat_page->current_hp));
	}

	//size_t loaded_gameobjects_count;
	//KHGameObject **loaded_gameobjects = get_loaded_gameobjects(&loaded_gameobjects_count);

	//if (loaded_gameobjects_count > 0) {
	//	for (int i = 0; i < loaded_gameobjects_count; i++) {
	//		if (loaded_gameobjects[i]->actor)
	//			print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->gameobject), std::string(loaded_gameobjects[i]->actor->name, 16)));
	//	}
	//} else {
	//	print_line("No loaded game objects found.");
	//}
}

//KH_MOD on_get_reward(DWORD64 reward_id) {
//	print_line("on_get_reward()");// std::format("on_get_reward(): reward_id: 0x{:X}", reward_id));
//}

KH_MOD on_get_hit() {
	print_line("on_get_hit()");
}