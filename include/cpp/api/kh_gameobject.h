#pragma once

#include <cstdint>
#include <string>

struct Vector4 {
	float x, y, z, w;
};

struct Color {
	float r, g, b, a;
};

struct Matrix4x4 {
	float a11, a12, a13, a14; 
	float a21, a22, a23, a24;
	float a31, a32, a33, a34;
	float a41, a42, a43, a44;
};

// size: 0x4B0
struct Entity {
	uint8_t unknown_1[0x4];

	uint32_t event_ID;					//0x4

	uint8_t unknown_2[0x8];

	Vector4 position;					//0x10

	uint8_t unknown_3[0x10];

	Vector4 rotation;					// 0x30 wraps around -PI - PI
	Vector4 scale;						// 0x40

	uint8_t unknown_4[0x1C];

	uint32_t stat_page_pointer;			//0x6C

	uint8_t unknown_5[0x30];

	Color color;						//0xA0

	uint8_t unknown_6[0x20];

	Matrix4x4 transform;				//0xD0

	uint8_t unknown_7[0x20];

	uint32_t actor_pointer;				// 0x130
	
	uint32_t unknown_pointer_1;			// 0x134
	uint32_t unknown_pointer_2;			// 0x138
	uint32_t unknown_pointer_3;			// 0x13C

	uint32_t portrait_frame_pointer;	// 0x140

	uint32_t unknown_pointer_4;			// 0x144
	uint32_t unknown_pointer_5;			// 0x148
	uint32_t unknown_pointer_6;			// 0x14C
	uint32_t unknown_pointer_7;			// 0x150
	uint32_t unknown_pointer_8;			// 0x154
	uint32_t unknown_pointer_9;			// 0x158
	uint32_t unknown_pointer_10;		// 0x15C

	uint8_t unknown_8[0x4];

	uint8_t animation_ID;				// 0x164

	uint8_t unknown_9[0x6B];

	uint32_t unknown_pointer_11;		// 0x1D0
	uint32_t unknown_pointer_12;		// 0x1D4
	uint32_t unknown_pointer_13;		// 0x1D8
	uint32_t unknown_pointer_14;		// 0x1DC

	uint8_t unknown_10[0xA4];

	float animation_speed;				// 0x284

	uint8_t unknown_11[0x28];

	Vector4 movement_speed;				// 0x2B0

	uint8_t unknown_12[0x20];

	Vector4 start_position;				// 0x2E0

	uint8_t unknown_13[0x30];

	Vector4 ground_raycast_hit;			// 0x320

	uint8_t unknown_14[0x20];

	Color color_pulse_animation;		// 0x350

	uint8_t unknown_15[0xF0];

	float head_anim_1;					// 0x450
	float head_anim_2;					// 0x454
	float head_orientation;				// 0x458 -1 = forward, 0 = invisible, 1 = backward

	uint8_t unknown_16[0x24];

	float scale_y_animation;			// 0x480 from <1 - 1

	uint8_t unknown_17[0x2C];
};

// size: 0x78
struct Actor {
	uint8_t unknown_1[0x18];

	uint32_t movable;					// 0x18

	uint8_t unknown_2[0x26];

	uint32_t treasure_chest_ID;			// 0x48

	uint8_t unknown_3[0x13];

	uint8_t interaction_ID;				// 0x5F
	uint32_t mdls_filename_pointer;		// 0x60
	uint32_t mset_filename_pointer;		// 0x64
	char name[16];						// 0x68
};

// size: 0x100
struct StatPage {
	uint8_t unknown_1[0x4];

	float walk_speed;					// 0x4
	float run_speed;					// 0x8

	uint8_t unknown_2[0x4];

	float jump_strength;				// 0x10

	uint8_t unknown_3[0x4];

	float air_acceleration;				// 0x18

	uint8_t unknown_4[0x20];

	uint32_t current_hp;				// 0x3C
	uint32_t max_hp;					// 0x40
	uint32_t current_mp;				// 0x44
	uint32_t max_mp;					// 0x48
	uint32_t strength;					// 0x4C
	uint32_t defense;					// 0x50

	uint8_t unknown_5[0x14];

	uint32_t exp_to_next_level;			// 0x68

	uint8_t unknown_6[0x14];

	float fire_resistance;				// 0x80
	float ice_resistance;				// 0x84
	float thunder_resistance;			// 0x88
	float dark_resistance;				// 0x8C

	uint8_t unknown_7[0x10];

	float unknown_resistance;			// 0xA0

	uint8_t unknown_8[0x1A];

	uint16_t mp_charge;					// 0xBE

	uint8_t unknown_9[0x8];

	uint64_t party_stat_page_pointer;	// 0xC8 

	uint8_t unknown_10[0x14];

	uint32_t max_ap;					// 0xE4

	uint8_t unknown_11[0x18];
};

// size: 0x74
struct PartyStatPage {
	uint8_t unknown_1[4];

	uint8_t level;						// 0x4
	uint8_t current_hp;					// 0x5
	uint8_t max_hp;						// 0x6
	uint8_t current_mp;					// 0x7
	uint8_t max_mp;						// 0x8
	uint8_t max_ap;						// 0x9
	uint8_t strength;					// 0xA
	uint8_t defense;					// 0xB

	uint8_t unknown_2[0x10];

	uint8_t max_accessories;			// 0x1C	
	uint8_t accessory_slots[8];			// 0x1D
	uint8_t max_items;					// 0x25
	uint8_t item_slots[8];				// 0x26

	uint8_t unknown_3[0x8];

	uint8_t equipped_weapon;			// 0x36

	uint8_t unknown_4[0x9];

	uint32_t experience;				// 0x40
	uint8_t ability_slots[48];			// 0x44
	union {
		uint8_t magic_unlocked;			// 0x74
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

class KHGameObject {
  public:
	Entity *entity;
	Actor *actor;
	StatPage *stat_page;
	PartyStatPage *party_stat_page;

	std::string to_string();
};