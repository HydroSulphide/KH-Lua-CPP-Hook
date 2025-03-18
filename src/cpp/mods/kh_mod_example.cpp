#include "kh_mod.h"

// Define metadata variables
string mod_name = "Example Mod";
string mod_author = "HydroSulphide";
string mod_description = "This is a description of Example Mod.";
string mod_version = "1.0.0";

KH_MOD on_init() {
	print_line("on_init()");
}

//std::string gummis[] = {"CURE_G", "CURAGA_G", "LIFE_G", "FULL_LIFE_G", "FIRE_G", "FIRA_G",	  "FIRAGA_G", "FLARE_G", "HOLY_G", "PROTECT_G_1", "PROTECT_G_2", "PROTECT_G_3", "PROTECT_G_4", "PROTECT_G_5", "PROTECT_G_6", "PROTECT_G_7", "PROTECT_G_8", "SHELL_G_1", "SHELL_G_2", "SHELL_G_3", "SHELL_G_4", "SHELL_G_5", "SHELL_G_6",  "SHELL_G_7", "SHELL_G_8", "DISPEL_G_1", "DISPEL_G_2", "DISPEL_G_3", "DISPEL_G_4", "DISPEL_G_5", "DISPEL_G_6", "DISPEL_G_7", "DISPEL_G_8", "AERORA_G_1",	"AERORA_G_2", "AERORA_G_3", "AERORA_G_4", "TORNADO_G_1", "TORNADO_G_2", "FLOAT_G_1", "AERO_G_1", "AERO_G_2", "AERO_G_3", "AERO_G_4", "DRAIN_G_1", "DRAIN_G_2", "OSMOSE_G_1", "OSMOSE_G_2", "TRANSFORM_G", "WARP_G", "SCAN_G_1", "SCAN_G_2", "HASTE_G", "HASTE2_G_", "SHIELD_G", "SHIELD2_G", "ESUNA_G_1",	 "ESUNA_G_2",	 "THUNDER_G", "THUNDARA_G", "THUNDAGA_G", "COMET_G", "METEOR_G",		"ULTIMA_G",		   "SPRAY",		"PALETTE",	 "SYS_UP1",	  "SYS_UP2",   "COM_LV1",	"COM_LV2",	 "COM_LV3",	  "KINGDOM",   "HYPERION",	"GEPETTO",	 "CID",		  "LEON",	   "YUFFIE",	"AERITH",	 "CACTUAR",	  "CHOCOBO",
//						"CINDY",  "SHIVA",	  "LAMIA",	"SANDY",	   "SYLPH",	 "CARBUNCLE", "MINDY",	  "GOBLIN",	 "BOMB",   "REMORA",	  "AHRIMAN",	 "IMP",			"SIREN",	   "STINGRAY",	  "CATOBLEPAS",	 "ADAMANT",		"SERPENT",	   "IFRIT",		"ODIN",		 "ATOMOS",	  "GOLEM",	   "DIABLOS",	"DEATHGUISE", "TYPHOON",   "ALEXANDER", "LEVIATHAN",  "RAMUH",		"OMEGA",	  "MOOGLES",	"VALEFOR",	  "PUPU",		"CERBERUS",	  "TONBERRY",	"PANDAEMONIUM", "IXION",	  "GILGAMESH",	"PHOENIX",	  "EDEN",		 "BAHAMUT",		"unused_1",	 "unused_2", "unused_3", "unused_4", "unused_5", "unused_6",  "unused_7",  "unused_8",	 "unused_9",   "WHEEL_G",	  "FANG_G", "HORN_G",	"ANGEL_G",	"DARK_G",  "SHOES_G",	"ROCK_G_1", "ROCK_G_2",	 "SCISSORS_G_1", "SCISSORS_G_2", "PAPER_G_1", "PAPER_G_2",	"CROWN_G",	  "DRILL_G", "CATERPILLAR_G_1", "CATERPILLAR_G_2", "unused_10", "unused_11", "unused_12", "unused_13", "unused_14", "unused_15", "unused_16", "unused_17", "unused_18", "unused_19", "unused_20", "unused_21", "unused_22", "unused_23", "unused_24", "unused_25"};

KH_MOD on_frame() {
	// TEST GUMMIS:

	KHGummi *gummis = get_gummis();

	// Test without special character and without repointing
	set_gummi_name(&gummis[CURE_G], L"Nice-G");
	set_gummi_description(&gummis[CURE_G], L"Short Description.");

	// Test with special character and repointing
	std::wstring new_fire_g_name = L"LONG» " KH_SYMBOL_ACCESSORY L" «NAME";
	set_gummi_name(&gummis[FIRE_G], new_fire_g_name.c_str());

	std::wstring new_fire_g_desc = L"This is a " KH_SYMBOL_ABILITY_STARS L"long" KH_SYMBOL_ABILITY_STARS L" sentence to test\nSpecial Characters and Repointing!";
	set_gummi_description(&gummis[FIRE_G], new_fire_g_desc.c_str());

	//KHGummiStats *fire_g_stats = gummis[FIRE_G].stats;
	//print_line(format("\nFIRE_G:\n\tLimit: {:d}", fire_g_stats->limit));
	//fire_g_stats->price_buy = 1;
	//fire_g_stats->limit = 35;

	// Print GUMMI NAMES:
	//uint64_t base_addr = 0x7ff7C0400000;
	//uint64_t start_addr = 0x7FF7C2A98622;
	//uint64_t stats_addr = 0x510240;
	//vector<uint64_t> stats_addresses;
	//vector<uint64_t> name_addresses;
	//vector<int> name_lengths;
	//vector<uint64_t> desc_addresses;
	//vector<int> desc_lengths;
	//uint64_t name_addr = start_addr;
	//uint64_t curr_pointer = name_addr;
	//int curr_char_count = 0;
	//int count = 0x80;
	//int length = 0;
	//bool found_zero_byte = false;
	//while (true) {
	//	if (*(reinterpret_cast<uint8_t *>(curr_pointer)) != 0x0) {
	//		length++;
	//		curr_pointer++;
	//		found_zero_byte = false;
	//	} else {
	//		//print_line(format("{{ stats_address = 0x{:X}, name_address = 0x{:X}, name_length = {:d} }} # {}", stats_addr, name_addr - base_addr, length, gummis[count]));
	//		stats_addresses.push_back(stats_addr);
	//		name_addresses.push_back(name_addr - base_addr);
	//		name_lengths.push_back(length);
	//		
	//		stats_addr += 0x1C;
	//		//stingray_name = { address = 0x7FF7C2A98549, length = 8 }
	//		length = 0,
	//		curr_pointer++;
	//		count++;
	//		name_addr = curr_pointer;
	//		if (found_zero_byte) {
	//			break;
	//		}
	//		found_zero_byte = true;
	//	}
	//}

	//start_addr = 0x7FF7C2A992C5;
	//uint64_t desc_addr = start_addr;
	//curr_pointer = desc_addr;
	//curr_char_count = 0;
	//count = 0x80;
	//length = 0;
	//found_zero_byte = false;
	//while (true) {
	//	if (*(reinterpret_cast<uint8_t *>(curr_pointer)) != 0x0) {
	//		length++;
	//		curr_pointer++;
	//		found_zero_byte = false;
	//	} else {
	//		// print_line(format("{{ stats_address = 0x{:X}, name_address = 0x{:X}, name_length = {:d} }} # {}", stats_addr, name_addr - base_addr, length, gummis[count]));
	//		desc_addresses.push_back(desc_addr - base_addr);
	//		desc_lengths.push_back(length);

	//		stats_addr += 0x1C;
	//		// stingray_name = { address = 0x7FF7C2A98549, length = 8 }
	//		length = 0, curr_pointer++;
	//		count++;
	//		desc_addr = curr_pointer;
	//		if (found_zero_byte) {
	//			break;
	//		}
	//		found_zero_byte = true;
	//	}
	//}

	//for (int i = 0; i < stats_addresses.size(); i++) {
	//	print_line(format("{{ stats_address = 0x{:X}, name_address = 0x{:X}, name_length = {:d}, desc_addresses = 0x{:X}, desc_length = {:d} }} # {}", stats_addresses[i], name_addresses[i], name_lengths[i], desc_addresses[i], desc_lengths[i], gummis[i+0x80]));
	//}



	// Print GUMMI STATS:
	//uint64_t start_addr = 0x7FF74247F440;
	//for (int i = 0; i < 0x90; i++) {
	//	uint64_t gummi_addr = start_addr + i * 0x1C;
	//	 Start with the first 4 bytes as characters
	//	std::string output = std::format("{:.4s}: ", reinterpret_cast<const char *>(gummi_addr));

	//	 Append the next 0x18 (24) bytes as hex values
	//	for (size_t i = 0; i < 0x18; ++i) {
	//		output += std::format("{:02X} ", *(reinterpret_cast<uint8_t *>(gummi_addr + 4 + i)));
	//	}

	//	 Print everything in one call (avoiding multiple new lines)
	//	print_line(output);
	//}


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