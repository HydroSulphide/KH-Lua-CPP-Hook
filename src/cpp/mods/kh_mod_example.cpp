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
	update_loaded_gameobjects();

	KHGameObject *sora = get_sora();
	if (sora) {
		sora->party_stat_page->current_hp = 18;
		sora->stat_page->current_hp = 18;
		print_line(std::format("SORA HP: {:d}", sora->party_stat_page->current_hp));
	} else {
		print_line("SORA not found!");
	}
}

//KH_MOD on_get_reward(DWORD64 reward_id) {
//	print_line("on_get_reward()");// std::format("on_get_reward(): reward_id: 0x{:X}", reward_id));
//}

//KH_MOD on_get_hit() {
//	print_line("on_get_hit()");
//}