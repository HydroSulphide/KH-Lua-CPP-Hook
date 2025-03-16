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
	//KHInventory *inventory = get_inventory();
	//print_line(std::format("Inventory:\n\tMunny: {:d}\n\tPotion: {:d}\n\tCure G: {:d}", *(inventory->munny), inventory->item_stock->potion, inventory->gummi_stock->cure_g));
	//*(inventory->munny) = 99999;

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

	
	KHGameObject *sora = get_sora();
	if (sora) {
		print_line("sora loaded!");
	}
	KHGameObject *donald = get_donald();
	if (donald) {
		print_line("donald loaded!");
	}
	KHGameObject *goofy = get_goofy();
	if (goofy) {
		print_line("goofy loaded!");
	}
	KHGameObject *tarzan = get_tarzan();
	if (tarzan) {
		print_line("tarzan loaded!");
	}
	KHGameObject *aladdin = get_aladdin();
	if (aladdin) {
		print_line("aladdin loaded!");
	}
	KHGameObject *ariel = get_ariel();
	if (ariel) {
		print_line("ariel loaded!");
	}
	KHGameObject *jack = get_jack();
	if (jack) {
		print_line("jack loaded!");
	}
	KHGameObject *peter_pan = get_peter_pan();
	if (peter_pan) {
		print_line("peter_pan loaded!");
	}
	KHGameObject *beast = get_beast();
	if (beast) {
		print_line("beast loaded!");
	}
	//if (sora && sora->object && sora->battle_stats && sora->attributes) {
	//	print_line(std::format("SORA HP: {:d}", sora->attributes->current_hp));
	//}


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