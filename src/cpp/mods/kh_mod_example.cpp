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
	KHInventory *inventory = get_inventory();
	print_line(std::format("Inventory:\n\tMunny: {:d}\n\tPotion: {:d}\n\tCure G: {:d}", *(inventory->munny), inventory->item_stock->potion, inventory->gummi_stock->cure_g));
	*(inventory->munny) = 99999;


	//KHGameObject *sora = get_sora();
	//if (sora && sora->party_stat_page) {
	//	print_line(std::format("SORA HP: {:d}", sora->party_stat_page->current_hp));
	//}


	//size_t loaded_gameobjects_count;
	//KHGameObject** loaded_gameobjects = get_loaded_gameobjects(&loaded_gameobjects_count);
	//if (loaded_gameobjects_count > 0) {
	//	for (int i = 0; i < loaded_gameobjects_count; i++) {
	//		if (loaded_gameobjects[i]->actor) {
	//			print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->gameobject), std::string(loaded_gameobjects[i]->actor->name, 16)));
	//			//if (strcmp(loaded_gameobjects[i]->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0) {
	//			//	print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->gameobject), std::string(loaded_gameobjects[i]->actor->name, 16)));
	//			//	print_line(std::format("\tActor: 0x{:X}", reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->actor)));
	//			//	print_line(std::format("\tStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->stat_page)));
	//			//	print_line(std::format("\tPartyStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->party_stat_page)));
	//			//} else if (strcmp(loaded_gameobjects[i]->actor->name, "WAKKA\0\0\0\0\0\0\0\0\0\0") == 0) {
	//			//	print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->gameobject), std::string(loaded_gameobjects[i]->actor->name, 16)));
	//			//}
	//		}
	//	}
	//} else {
	//	print_line("No loaded game objects found.");
	//}
}

//KH_MOD on_get_reward(DWORD64 reward_id) {
//	print_line("on_get_reward()");// std::format("on_get_reward(): reward_id: 0x{:X}", reward_id));
//}

KH_MOD on_get_hit(KHGameObject *kh_gameobject) {
	//print_line("on_get_hit()");
	//if (kh_gameobject && kh_gameobject->actor) {
	//	print_line(std::format("Object 0x{:X}: {}", reinterpret_cast<uintptr_t>(kh_gameobject->gameobject), std::string(kh_gameobject->actor->name, 16)));
	//	//print_line(std::format("\tActor: 0x{:X}", reinterpret_cast<uintptr_t>(kh_gameobject->actor)));
	//	//print_line(std::format("\tStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(kh_gameobject->stat_page)));
	//	//print_line(std::format("\tPartyStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(kh_gameobject->party_stat_page)));
	//}
}

KH_MOD on_attack(KHGameObject *kh_gameobject) {
	//print_line("on_attack()");
	//if (kh_gameobject && kh_gameobject->actor) {
	//	print_line(std::format("Object 0x{:X}: {}", reinterpret_cast<uintptr_t>(kh_gameobject->gameobject), std::string(kh_gameobject->actor->name, 16)));
	//	//print_line(std::format("\tActor: 0x{:X}", reinterpret_cast<uintptr_t>(kh_gameobject->actor)));
	//	//print_line(std::format("\tStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(kh_gameobject->stat_page)));
	//	//print_line(std::format("\tPartyStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(kh_gameobject->party_stat_page)));
	//}
}