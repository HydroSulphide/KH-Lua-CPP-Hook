#pragma once

#include <cstdint>

struct KHItemStock {
	uint8_t none;				// 0x0
	uint8_t potion;				// 0x1
	uint8_t hi_potion;			// 0x2
	uint8_t ether;				// 0x3
	uint8_t elixir;				// 0x4

	uint8_t unused_1;

	uint8_t mega_potion;		// 0x6
	uint8_t mega_ether;			// 0x7
	uint8_t megalixir;			// 0x8
	uint8_t fury_stone;			// 0x9
	uint8_t power_stone;		// 0xA
	uint8_t energy_stone;		// 0xB
	uint8_t blazing_stone;		// 0xC
	uint8_t frost_stone;		// 0xD
	uint8_t lightning_stone;	// 0xE
	uint8_t dazzling_stone;		// 0xF
	uint8_t stormy_stone;		// 0x10
	uint8_t protect_chain;		// 0x11
	uint8_t protera_chain;		// 0x12
	uint8_t protega_chain;		// 0x13
	uint8_t fire_ring;			// 0x14
	uint8_t fira_ring;			// 0x15
	uint8_t firaga_ring;		// 0x16
	uint8_t blizzard_ring;		// 0x17
	uint8_t blizzara_ring;		// 0x18
	uint8_t blizzaga_ring;		// 0x19
	uint8_t thunder_ring;		// 0x1A
	uint8_t thundara_ring;		// 0x1B
	uint8_t thundaga_ring;		// 0x1C
	uint8_t ability_stud;		// 0x1D
	uint8_t guard_earring;		// 0x1E
	uint8_t master_earring;		// 0x1F
	uint8_t chaos_ring;			// 0x20
	uint8_t dark_ring;			// 0x21
	uint8_t element_ring;		// 0x22
	uint8_t three_stars;		// 0x23
	uint8_t power_chain;		// 0x24
	uint8_t golem_chain;		// 0x25
	uint8_t titan_chain;		// 0x26
	uint8_t energy_bangle;		// 0x27
	uint8_t angel_bangle;		// 0x28
	uint8_t gaia_bangle;		// 0x29
	uint8_t magic_armlet;		// 0x2A
	uint8_t rune_armlet;		// 0x2B
	uint8_t atlas_armlet;		// 0x2C
	uint8_t heartguard;			// 0x2D
	uint8_t ribbon;				// 0x2E
	uint8_t crystal_crown;		// 0x2F
	uint8_t brave_warrior;		// 0x30
	uint8_t ifrits_horn;		// 0x31
	uint8_t inferno_band;		// 0x32
	uint8_t white_fang;			// 0x33
	uint8_t ray_of_light;		// 0x34
	uint8_t holy_circlet;		// 0x35
	uint8_t ravens_claw;		// 0x36
	uint8_t omega_arts;			// 0x37
	uint8_t exp_earring;		// 0x38

	uint8_t unused_2;

	uint8_t exp_ring;			// 0x3A
	uint8_t exp_bracelet;		// 0x3B
	uint8_t exp_necklace;		// 0x3C
	uint8_t firagun_band;		// 0x3D
	uint8_t blizzagun_band;		// 0x3E
	uint8_t thundagun_band;		// 0x3F
	uint8_t ifrit_belt;			// 0x40
	uint8_t shiva_belt;			// 0x41
	uint8_t ramuh_belt;			// 0x42
	uint8_t moogle_badge;		// 0x43
	uint8_t cosmic_arts;		// 0x44
	uint8_t royal_crown;		// 0x45
	uint8_t prime_cap;			// 0x46
	uint8_t obsidian_ring;		// 0x47

	uint8_t unused_3;
	uint8_t unused_4;
	uint8_t unused_5;
	uint8_t unused_6;
	uint8_t unused_7;
	uint8_t unused_8;
	uint8_t unused_9;
	uint8_t unused_10;
	uint8_t unused_11;

	uint8_t kingdom_key;		// 0x51
	uint8_t dream_sword;		// 0x52
	uint8_t dream_shiel_sora;	// 0x53
	uint8_t dream_rod_sora;		// 0x54
	uint8_t wooden_sword;		// 0x55
	uint8_t jungle_king;		// 0x56
	uint8_t three_wishes;		// 0x57
	uint8_t fairy_harp;			// 0x58
	uint8_t pumpkin_head;		// 0x59
	uint8_t crabclaw;			// 0x5A
	uint8_t divine_rose;		// 0x5B
	uint8_t spellbinder;		// 0x5C
	uint8_t olympia;			// 0x5D
	uint8_t lionheart;			// 0x5E
	uint8_t metal_chocobo;		// 0x5F
	uint8_t oathkeeper;			// 0x60
	uint8_t oblivion;			// 0x61
	uint8_t lady_luck;			// 0x62
	uint8_t wishing_star;		// 0x63
	uint8_t ultima_weapon;		// 0x64
	uint8_t diamond_dust;		// 0x65
	uint8_t one_winged_angel;	// 0x66
	uint8_t mages_staff;		// 0x67
	uint8_t morning_star;		// 0x68
	uint8_t shooting_star;		// 0x69
	uint8_t magus_staff;		// 0x6A
	uint8_t wisdom_staff;		// 0x6B
	uint8_t warhammer;			// 0x6C
	uint8_t silver_mallet;		// 0x6D
	uint8_t grand_mallet;		// 0x6E
	uint8_t lord_fortune;		// 0x6F
	uint8_t violetta;			// 0x70
	uint8_t dream_rod_donald;	// 0x71
	uint8_t save_the_queen;		// 0x72
	uint8_t wizards_relic;		// 0x73
	uint8_t meteor_strike;		// 0x74
	uint8_t fantasista;			// 0x75

	uint8_t unused_12;

	uint8_t knights_shield;		// 0x77
	uint8_t mythril_shield;		// 0x78
	uint8_t onyx_shield;		// 0x79
	uint8_t stout_shield;		// 0x7A
	uint8_t golem_shield;		// 0x7B
	uint8_t adamant_shield;		// 0x7C
	uint8_t smasher;			// 0x7D
	uint8_t gigas_fist;			// 0x7E
	uint8_t genji_shield;		// 0x7F
	uint8_t hercs_shield;		// 0x80
	uint8_t dream_shield_goofy; // 0x81
	uint8_t save_the_king;		// 0x82
	uint8_t defender;			// 0x83
	uint8_t mighty_shield;		// 0x84
	uint8_t seven_elements;		// 0x85

	uint8_t unused_13;

	uint8_t spear;				// 0x87
	uint8_t no_weapon_1;		// 0x88
	uint8_t sword;				// 0x89
	uint8_t no_weapon_2;		// 0x8A
	uint8_t no_weapon_3;		// 0x8B
	uint8_t dagger;				// 0x8C
	uint8_t claws;				// 0x8D
	uint8_t tent;				// 0x8E
	uint8_t camping_set;		// 0x8F
	uint8_t cottage;			// 0x90

	uint8_t unused_14;
	uint8_t unused_15;
	uint8_t unused_16;
	uint8_t unused_17;

	uint8_t ansems_report_11;	// 0x95
	uint8_t ansems_report_12;	// 0x96
	uint8_t ansems_report_13;	// 0x97
	uint8_t power_up;			// 0x98
	uint8_t defense_up;			// 0x99
	uint8_t ap_up;				// 0x9A
	uint8_t serenity_power;		// 0x9B
	uint8_t dark_matter;		// 0x9C
	uint8_t mythril_stone;		// 0x9D
	uint8_t fire_arts;			// 0x9E
	uint8_t blizzard_arts;		// 0x9F
	uint8_t thunder_arts;		// 0xA0
	uint8_t cure_arts;			// 0xA1
	uint8_t gravity_arts;		// 0xA2
	uint8_t stop_arts;			// 0xA3
	uint8_t aero_arts;			// 0xA4
	uint8_t shiitake_rank;		// 0xA5
	uint8_t matsuake_rank;		// 0xA6
	uint8_t mystery_mold;		// 0xA7
	uint8_t ansems_report_1;	// 0xA8
	uint8_t ansems_report_2;	// 0xA9
	uint8_t ansems_report_3;	// 0xAA
	uint8_t ansems_report_4;	// 0xAB
	uint8_t ansems_report_5;	// 0xAC
	uint8_t ansems_report_6;	// 0xAD
	uint8_t ansems_report_7;	// 0xAE
	uint8_t ansems_report_8;	// 0xAF
	uint8_t ansems_report_9;	// 0xB0
	uint8_t ansems_report_10;	// 0xB1
	uint8_t khama_vol_8;		// 0xB2
	uint8_t salegg_vol_6;		// 0xB3
	uint8_t azal_vol_3;			// 0xB4
	uint8_t mava_vol_3;			// 0xB5
	uint8_t mava_vol_6;			// 0xB6
	uint8_t theon_vol_6;		// 0xB7
	uint8_t nahara_vol_5;		// 0xB8
	uint8_t hafet_vol_4;		// 0xB9
	uint8_t empty_bottle;		// 0xBA
	uint8_t old_book;			// 0xBB
	uint8_t emblem_piece_1;		// 0xBC
	uint8_t emblem_piece_2;		// 0xBD
	uint8_t emblem_piece_3;		// 0xBE
	uint8_t emblem_piece_4;		// 0xBF
	uint8_t log;				// 0xC0
	uint8_t cloth;				// 0xC1
	uint8_t rope;				// 0xC2
	uint8_t seagull_egg;		// 0xC3
	uint8_t fish;				// 0xC4
	uint8_t mushroom;			// 0xC5
	uint8_t coconut;			// 0xC6
	uint8_t drinking_water;		// 0xC7
	uint8_t navi_g_piece_dj;	// 0xC8
	uint8_t navi_g_piece_wl;	// 0xC9
	uint8_t navi_gummi_1;		// 0xCA
	uint8_t navi_g_piece_tt;	// 0xCB
	uint8_t navi_g_piece_nl;	// 0xCC
	uint8_t navi_gummi_2;		// 0xCD
	uint8_t watergleam;			// 0xCE
	uint8_t naturespark;		// 0xCF
	uint8_t fireglow;			// 0xD0
	uint8_t earthshine;			// 0xD1
	uint8_t crystal_trident;	// 0xD2
	uint8_t postcard;			// 0xD3
	uint8_t torn_page_1;		// 0xD4
	uint8_t torn_page_2;		// 0xD5
	uint8_t torn_page_3;		// 0xD6
	uint8_t torn_page_4;		// 0xD7
	uint8_t torn_page_5;		// 0xD8
	uint8_t slide_1;			// 0xD9
	uint8_t slide_2;			// 0xDA
	uint8_t slide_3;			// 0xDB
	uint8_t slide_4;			// 0xDC
	uint8_t slide_5;			// 0xDD
	uint8_t slide_6;			// 0xDE
	uint8_t footprints;			// 0xDF
	uint8_t claw_marks;			// 0xE0
	uint8_t stench;				// 0xE1
	uint8_t antenna;			// 0xE2
	uint8_t forget_me_not;		// 0xE3
	uint8_t jack_in_the_box;	// 0xE4
	uint8_t entry_pass;			// 0xE5
	uint8_t hero_license;		// 0xE6
	uint8_t pretty_stone;		// 0xE7

	uint8_t unused_18;

	uint8_t lucid_shard;		// 0xE9
	uint8_t lucid_gem;			// 0xEA
	uint8_t lucid_crystal;		// 0xEB
	uint8_t spirit_shard;		// 0xEC
	uint8_t spirit_gem;			// 0xED
	uint8_t power_shard;		// 0xEE
	uint8_t power_gem;			// 0xEF
	uint8_t power_crystal;		// 0xF0
	uint8_t blaze_shard;		// 0xF1
	uint8_t blaze_gem;			// 0xF2
	uint8_t frost_shard;		// 0xF3
	uint8_t frost_gem;			// 0xF4
	uint8_t thunder_shard;		// 0xF5
	uint8_t thunder_gem;		// 0xF6
	uint8_t shiny_crystal;		// 0xF7
	uint8_t bright_shard;		// 0xF8
	uint8_t bright_gem;			// 0xF9
	uint8_t btright_crystal;	// 0xFA
	uint8_t mystery_goo;		// 0xFB
	uint8_t gale;				// 0xFC
	uint8_t mythril_shard;		// 0xFD
	uint8_t mythril;			// 0xFE
	uint8_t orichalcum;			// 0xFF
};

struct KHGummiStock {
	uint8_t cure_g;			 // 0x0
	uint8_t curaga_g;		 // 0x1
	uint8_t life_g;			 // 0x2
	uint8_t full_life_g;	 // 0x3
	uint8_t fire_g;			 // 0x4
	uint8_t fira_g;			 // 0x5
	uint8_t firaga_g;		 // 0x6
	uint8_t flare_g;		 // 0x7
	uint8_t holy_g;			 // 0x8
	uint8_t protect_g_1;	 // 0x9
	uint8_t protect_g_2;	 // 0xA
	uint8_t protect_g_3;	 // 0xB
	uint8_t protect_g_4;	 // 0xC
	uint8_t protect_g_5;	 // 0xD
	uint8_t protect_g_6;	 // 0xE
	uint8_t protect_g_7;	 // 0xF
	uint8_t protect_g_8;	 // 0x10
	uint8_t shell_g_1;		 // 0x11
	uint8_t shell_g_2;		 // 0x12
	uint8_t shell_g_3;		 // 0x13
	uint8_t shell_g_4;		 // 0x14
	uint8_t shell_g_5;		 // 0x15
	uint8_t shell_g_6;		 // 0x16
	uint8_t shell_g_7;		 // 0x17
	uint8_t shell_g_8;		 // 0x18
	uint8_t dispel_g_1;		 // 0x19
	uint8_t dispel_g_2;		 // 0x1A
	uint8_t dispel_g_3;		 // 0x1B
	uint8_t dispel_g_4;		 // 0x1C
	uint8_t dispel_g_5;		 // 0x1D
	uint8_t dispel_g_6;		 // 0x1E
	uint8_t dispel_g_7;		 // 0x1F
	uint8_t dispel_g_8;		 // 0x20
	uint8_t aerora_g_1;		 // 0x21
	uint8_t aerora_g_2;		 // 0x22
	uint8_t aerora_g_3;		 // 0x23
	uint8_t aerora_g_4;		 // 0x24
	uint8_t tornado_g_1;	 // 0x25
	uint8_t tornado_g_2;	 // 0x26
	uint8_t float_g_1;		 // 0x27
	uint8_t aero_g_1;		 // 0x28
	uint8_t aero_g_2;		 // 0x29
	uint8_t aero_g_3;		 // 0x2A
	uint8_t aero_g_4;		 // 0x2B
	uint8_t drain_g_1;		 // 0x2C
	uint8_t drain_g_2;		 // 0x2D
	uint8_t osmose_g_1;		 // 0x2E
	uint8_t osmose_g_2;		 // 0x2F
	uint8_t transform_g;	 // 0x30
	uint8_t warp_g;			 // 0x31
	uint8_t scan_g_1;		 // 0x32
	uint8_t scan_g_2;		 // 0x33
	uint8_t haste_g;		 // 0x34
	uint8_t haste2_g_;		 // 0x35
	uint8_t shield_g;		 // 0x36
	uint8_t shield2_g;		 // 0x37
	uint8_t esuna_g_1;		 // 0x38
	uint8_t esuna_g_2;		 // 0x39
	uint8_t thunder_g;		 // 0x3A
	uint8_t thundara_g;		 // 0x3B
	uint8_t thundaga_g;		 // 0x3C
	uint8_t comet_g;		 // 0x3D
	uint8_t meteor_g;		 // 0x3E
	uint8_t ultima_g;		 // 0x3F
	uint8_t spray;			 // 0x40
	uint8_t palette;		 // 0x41
	uint8_t sys_up1;		 // 0x42
	uint8_t sys_up2;		 // 0x43
	uint8_t com_lv1;		 // 0x44
	uint8_t com_lv2;		 // 0x45
	uint8_t com_lv3;		 // 0x46
	uint8_t kingdom;		 // 0x47
	uint8_t hyperion;		 // 0x48
	uint8_t gepetto;		 // 0x49
	uint8_t cid;			 // 0x4A
	uint8_t leon;			 // 0x4B
	uint8_t yuffie;			 // 0x4C
	uint8_t aerith;			 // 0x4D
	uint8_t cactuar;		 // 0x4E
	uint8_t chocobo;		 // 0x4F
	uint8_t cindy;			 // 0x50
	uint8_t shiva;			 // 0x51
	uint8_t lamia;			 // 0x52
	uint8_t sandy;			 // 0x53
	uint8_t sylph;			 // 0x54
	uint8_t carbuncle;		 // 0x55
	uint8_t mindy;			 // 0x56
	uint8_t goblin;			 // 0x57
	uint8_t bomb;			 // 0x58
	uint8_t remora;			 // 0x59
	uint8_t ahriman;		 // 0x5A
	uint8_t imp;			 // 0x5B
	uint8_t siren;			 // 0x5C
	uint8_t stingray;		 // 0x5D
	uint8_t catoblepas;		 // 0x5E
	uint8_t adamant;		 // 0x5F
	uint8_t serpent;		 // 0x60
	uint8_t ifrit;			 // 0x61
	uint8_t odin;			 // 0x62
	uint8_t atomos;			 // 0x63
	uint8_t golem;			 // 0x64
	uint8_t diablos;		 // 0x65
	uint8_t deathguise;		 // 0x66
	uint8_t typhoon;		 // 0x67
	uint8_t alexander;		 // 0x68
	uint8_t leviathan;		 // 0x69
	uint8_t ramuh;			 // 0x6A
	uint8_t omega;			 // 0x6B
	uint8_t moogles;		 // 0x6C
	uint8_t valefor;		 // 0x6D
	uint8_t pupu;			 // 0x6E
	uint8_t cerberus;		 // 0x6F
	uint8_t tonberry;		 // 0x70
	uint8_t pandaemonium;	 // 0x71
	uint8_t ixion;			 // 0x72
	uint8_t gilgamesh;		 // 0x73
	uint8_t phoenix;		 // 0x74
	uint8_t eden;			 // 0x75
	uint8_t bahamut;		 // 0x76

	uint8_t unused_1;		 // 0x77
	uint8_t unused_2;		 // 0x78
	uint8_t unused_3;		 // 0x79
	uint8_t unused_4;		 // 0x7A
	uint8_t unused_5;		 // 0x7B
	uint8_t unused_6;		 // 0x7C
	uint8_t unused_7;		 // 0x7D
	uint8_t unused_8;		 // 0x7E
	uint8_t unused_9;		 // 0x7F

	uint8_t wheel_g;		 // 0x80
	uint8_t fang_g;			 // 0x81
	uint8_t horn_g;			 // 0x82
	uint8_t angel_g;		 // 0x83
	uint8_t dark_g;			 // 0x84
	uint8_t shoes_g;		 // 0x85
	uint8_t rock_g_1;		 // 0x86
	uint8_t rock_g_2;		 // 0x87
	uint8_t scissors_g_1;	 // 0x88
	uint8_t scissors_g_2;	 // 0x89
	uint8_t paper_g_1;		 // 0x8A
	uint8_t paper_g_2;		 // 0x8B
	uint8_t crown_g;		 // 0x8C
	uint8_t drill_g;		 // 0x8D
	uint8_t caterpillar_g_1; // 0x8E
	uint8_t caterpillar_g_2; // 0x8F

	uint8_t unused_10;		 // 0x90
	uint8_t unused_11;		 // 0x91
	uint8_t unused_12;		 // 0x92
	uint8_t unused_13;		 // 0x93
	uint8_t unused_14;		 // 0x94
	uint8_t unused_15;		 // 0x95
	uint8_t unused_16;		 // 0x96
	uint8_t unused_17;		 // 0x97
	uint8_t unused_18;		 // 0x98
	uint8_t unused_19;		 // 0x99
	uint8_t unused_20;		 // 0x9A
	uint8_t unused_21;		 // 0x9B
	uint8_t unused_22;		 // 0x9C
	uint8_t unused_23;		 // 0x9D
	uint8_t unused_24;		 // 0x9E
	uint8_t unused_25;		 // 0x9F
};

struct KHInventory {
	KHItemStock *item_stock;
	KHGummiStock *gummi_stock;
	uint32_t *munny;
};