#pragma once

#include <vector>

extern uintptr_t *loaded_gameobjects_start_pointer;
extern size_t max_loaded_gameobjects;

extern uintptr_t loaded_gameobject_addresses[30];

void update_loaded_gameobject_addresses();
void init_kh_inventory(uint64_t item_stock_address, uint64_t gummi_stock_address, uint64_t munny_address);
void init_kh_party(uint64_t shared_abilities_address, uint64_t magic_tiers_address, uint64_t exp_multiplier_address, uint64_t lvlup_tables_address);
void init_kh_attributes(uint64_t sora_attr_addr, uint64_t donald_attr_addr, uint64_t goofy_attr_addr, uint64_t tarzan_attr_addr, uint64_t aladdin_attr_addr, uint64_t ariel_attr_addr, uint64_t jack_attr_addr, uint64_t peter_pan_attr_addr, uint64_t beast_attr_addr);