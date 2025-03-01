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
	KHGameObject *sora = new KHGameObject;
	if (get_object_addr() != 0) {
		sora->gameobject = reinterpret_cast<GameObject *>(get_object_addr());
		sora->actor = reinterpret_cast<Actor *>(get_actor_addr());
		sora->stat_page = reinterpret_cast<StatPage *>(get_stat_page_addr());
		sora->party_stat_page = reinterpret_cast<PartyStatPage *>(get_party_stat_page_addr());
		print_line(std::format("SORA HP: {:d}", sora->party_stat_page->current_hp));
	}
}

//KH_MOD on_get_reward(DWORD64 reward_id) {
//	print_line("on_get_reward()");// std::format("on_get_reward(): reward_id: 0x{:X}", reward_id));
//}

//KH_MOD on_get_hit() {
//	print_line("on_get_hit()");
//}