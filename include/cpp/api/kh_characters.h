#pragma once

#include <cstdint>

struct CharacterStats {
	uint8_t level;
	uint8_t current_hp;
	uint8_t max_hp;
	uint8_t current_mp;
	uint8_t max_mp;
	uint8_t max_ap;
	uint8_t strength;
	uint8_t defense;

	uint8_t unknown_1[11];

	uint8_t max_accessories;
	uint8_t accessory_slots[8];
	uint8_t max_items;
	uint8_t item_slots[8];

	uint8_t unknown_2[8];

	uint8_t equipped_weapon;

	uint8_t unknown_3[9];

	uint32_t experience;
	uint8_t ability_slots[48];
	union {
		uint8_t magic_unlocked;
		struct {
			uint8_t fire : 1;
			uint8_t blizzard : 1;
			uint8_t thunder : 1;
			uint8_t cure : 1;
			uint8_t gravity : 1;
			uint8_t stop : 1;
			uint8_t aero : 1;
			uint8_t unused : 1;
		} magic;
	};
};

extern CharacterStats *sora_character_stats;
extern CharacterStats *donald_sharacter_stats;
extern CharacterStats *goofy_character_stats;

struct FieldStats {
	uint8_t unknown_1[108];

	uint32_t current_hp;
	uint32_t max_hp;
	uint32_t current_mp;
	uint32_t max_mp;
	uint32_t strength;
	uint32_t defense;

	uint8_t unknown_2[44];

	uint32_t fire_resistance;
	uint32_t ice_resistance;
	uint32_t thunder_resistance;
	uint32_t dark_resistance;

	uint8_t unknown_3[16];

	uint32_t unknown_resistance;

	uint8_t unknown_4[38];

	uint32_t max_ap;
};

extern FieldStats *sora_field_stats;
extern FieldStats *donald_field_stats;
extern FieldStats *goofy_field_stats;

void character_stats_init(uintptr_t base_address, uintptr_t offset_sora, uintptr_t offset_donald, uintptr_t offset_goofy);

void field_stats_init(uintptr_t base_address, uintptr_t offset_sora, uintptr_t offset_donald, uintptr_t offset_goofy);