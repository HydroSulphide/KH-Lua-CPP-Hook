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
	// TEST INVENTORY:
	//KHInventory *inventory = get_inventory();
	//print_line(std::format("Inventory:\n\tMunny: {:d}\n\tPotion: {:d}\n\tCure G: {:d}", *(inventory->munny), inventory->item_stock->potion, inventory->gummi_stock->cure_g));
	//*(inventory->munny) = 99999;



	// TEST PARTY:
	//KHParty *party = get_party();
	//print_line(std::format("Beast EXP from Level 62 to Level 63: {:d}", party->beast_lvlup_exp_table->lvl_63));
	//
	//party->shared_abilities->slot_1 = 0x1C;
	//party->shared_abilities->slot_2 = 0x1C;
	//party->shared_abilities->slot_3 = 0x1C;
	//party->shared_abilities->slot_4 = 0x1C;
	//party->shared_abilities->slot_5 = 0x1C;
	//
	//party->magic_tiers->fire = 1;
	//party->magic_tiers->blizzard = 2;
	//party->magic_tiers->thunder = 3;
	//party->magic_tiers->cure = 1;
	//party->magic_tiers->gravity = 2;
	//party->magic_tiers->stop = 3;
	//party->magic_tiers->aero = 1;
	//
	//*(party->exp_multiplier) = 2;
	//
	//party->sora_lvlup_exp_table_midday->lvl_62 = 17000;
	//party->donald_lvlup_exp_table->lvl_62 = 17200;
	//party->goofy_lvlup_exp_table->lvl_64 = 12000;
	//party->beast_lvlup_exp_table->lvl_63 = 18300;
	//
	//party->sora_lvlup_table->lvl_62 = LVLUP_MAX_MP;
	//party->sora_lvlup_table_bonus_sword->lvl_62 = LVLUP_MAX_MP;
	//party->donald_lvlup_table->lvl_62 = LVLUP_MAX_HP;
	//party->donald_lvlup_table_bonus->lvl_62 = LVLUP_MAX_ACCESSORIES;
	//party->goofy_lvlup_table->lvl_64 = LVLUP_MAX_ITEMS;
	//party->goofy_lvlup_table_bonus->lvl_64 = LVLUP_MAX_ACCESSORIES;
	//party->beast_lvlup_table->lvl_63 = LVLUP_STRENGTH;
	//party->beast_lvlup_table_bonus->lvl_63 = LVLUP_STRENGTH;

	
	// TEST LOADED PARTY MEMBERS:
	//KHGameObject *sora = get_sora();
	//if (sora) {
	//	sora->battle_stats->current_mp = 5;
	//	sora->attributes->current_mp = 5;
	//	print_line(std::format("sora (0x{:X}) loaded!", reinterpret_cast<uint64_t>(sora->attributes)));
	//}
	//KHGameObject *donald = get_donald();
	//if (donald) {
	//	donald->battle_stats->current_mp = 3;
	//	donald->attributes->current_mp = 3;
	//	print_line(std::format("donald (0x{:X}) loaded!", reinterpret_cast<uint64_t>(donald->attributes)));
	//}
	//KHGameObject *goofy = get_goofy();
	//if (goofy) {
	//	goofy->battle_stats->current_hp = 10;
	//	goofy->attributes->current_hp = 10;
	//	print_line(std::format("goofy (0x{:X}) loaded!", reinterpret_cast<uint64_t>(goofy->attributes)));
	//}
	//KHGameObject *tarzan = get_tarzan();
	//if (tarzan) {
	//	tarzan->battle_stats->current_mp = 1;
	//	tarzan->attributes->current_mp = 1;
	//	print_line(std::format("tarzan (0x{:X}) loaded!", reinterpret_cast<uint64_t>(tarzan->attributes)));
	//}
	//KHGameObject *aladdin = get_aladdin();
	//if (aladdin) {
	//	aladdin->battle_stats->current_mp = 1;
	//	aladdin->attributes->current_mp = 1;
	//	print_line(std::format("aladdin (0x{:X}) loaded!", reinterpret_cast<uint64_t>(aladdin->attributes)));
	//}
	//KHGameObject *ariel = get_ariel();
	//if (ariel) {
	//	ariel->battle_stats->current_mp = 1;
	//	ariel->attributes->current_mp = 1;
	//	print_line(std::format("ariel (0x{:X}) loaded!", reinterpret_cast<uint64_t>(ariel->attributes)));
	//}
	//KHGameObject *jack = get_jack();
	//if (jack) {
	//	jack->battle_stats->current_mp = 2;
	//	jack->attributes->current_mp = 3;
	//	print_line(std::format("jack (0x{:X}) loaded!", reinterpret_cast<uint64_t>(jack->attributes)));
	//}
	//KHGameObject *peter_pan = get_peter_pan();
	//if (peter_pan) {
	//	peter_pan->battle_stats->current_mp = 1;
	//	peter_pan->attributes->current_mp = 1;
	//	print_line(std::format("peter_pan (0x{:X}) loaded!", reinterpret_cast<uint64_t>(peter_pan->attributes)));
	//}
	//KHGameObject *beast = get_beast();
	//if (beast) {
	//	beast->battle_stats->current_mp = 1;
	//	beast->attributes->current_mp = 1;
	//	print_line(std::format("beast (0x{:X}) loaded!", reinterpret_cast<uint64_t>(beast->attributes)));
	//}



	// TEST ATTRIBUTES:
	//KHAttributes *sora_attributes = get_sora_attributes();
	//print_line(format("SORA HP: {:d}", sora_attributes->current_hp));



	// TEST LOADED GAMEOBJECTS:
	//size_t loaded_gameobjects_count;
	//KHGameObject** loaded_gameobjects = get_loaded_gameobjects(&loaded_gameobjects_count);
	//if (loaded_gameobjects_count > 0) {
	//	for (int i = 0; i < loaded_gameobjects_count; i++) {
	//		if (loaded_gameobjects[i]->model) {
	//			print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->object), std::string(loaded_gameobjects[i]->model->name, 16)));
	//			//if (strcmp(loaded_gameobjects[i]->actor->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0) {
	//			//	print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->gameobject), std::string(loaded_gameobjects[i]->actor->name, 16)));
	//			//	print_line(std::format("\tActor: 0x{:X}", reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->actor)));
	//			//	print_line(std::format("\tStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->stat_page)));
	//			//	print_line(std::format("\tPartyStatPage: 0x{:X}", reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->party_stat_page)));
	//			//} else if (strcmp(loaded_gameobjects[i]->actor->name, "WAKKA\0\0\0\0\0\0\0\0\0\0") == 0) {
	//			//	print_line(std::format("Object {:d} (0x{:X}): {}", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->gameobject), std::string(loaded_gameobjects[i]->actor->name, 16)));
	//			//}
	//		} else {
	//			print_line(std::format("Object {:d} (0x{:X}): No Model found!", i, reinterpret_cast<uintptr_t>(loaded_gameobjects[i]->object)));
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