#pragma once

#include <vector>
#include <string>

struct TOMLKHGummi {
	uint64_t stats_address;
	uint64_t name_address;
	size_t name_length;
	uint64_t description_address;
	size_t description_length;
};

struct TOMLKHItem {
	uint64_t item_stats_address;
	uint64_t accessory_stats_address;
	uint64_t weapon_stats_address;
};

extern uintptr_t *loaded_gameobjects_start_pointer;
extern size_t max_loaded_gameobjects;

extern uintptr_t loaded_gameobject_addresses[30];

struct KHStringRepoint {
	uint64_t old_address;
	std::string new_string;
};

extern std::vector<KHStringRepoint> string_repoints;

void update_loaded_gameobject_addresses();
void init_kh_inventory(uint64_t item_stock_address, uint64_t gummi_stock_address, uint64_t munny_address);
void init_kh_party(uint64_t shared_abilities_address, uint64_t magic_tiers_address, uint64_t exp_multiplier_address, uint64_t lvlup_tables_address);
void init_kh_attributes(uint64_t sora_attr_addr, uint64_t donald_attr_addr, uint64_t goofy_attr_addr, uint64_t tarzan_attr_addr, uint64_t aladdin_attr_addr, uint64_t ariel_attr_addr, uint64_t jack_attr_addr, uint64_t peter_pan_attr_addr, uint64_t beast_attr_addr);
void init_kh_gummis(std::vector<TOMLKHGummi> gummis_toml_data);
void init_kh_items(std::vector<TOMLKHItem> items_toml_data);

void init_kh_item_names_offset_address(uint64_t item_names_offset_addr);
void init_kh_item_names();

void init_kh_splash_screen_done_flag(uint64_t splash_screen_done_flag_address);
void on_splash_screen();