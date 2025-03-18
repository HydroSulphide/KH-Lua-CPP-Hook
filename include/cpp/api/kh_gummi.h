#pragma once

#include <cstdint>
#include <string>

enum KHGummiID {
	CURE_G = 0x0,
	CURAGA_G = 0x1,
	LIFE_G = 0x2,
	FULL_LIFE_G = 0x3,
	FIRE_G = 0x4,
	FIRA_G = 0x5,
	FIRAGA_G = 0x6,
	FLARE_G = 0x7,
	HOLY_G = 0x8,
	PROTECT_G_SCB = 0x9,
	PROTECT_G_STP = 0xA,
	PROTECT_G_STS = 0xB,
	PROTECT_G_SCL = 0xC,
	PROTECT_G_SCQ = 0xD,
	PROTECT_G_SSP = 0xE,
	PROTECT_G_SPD = 0xF,
	PROTECT_G_SDM = 0x10,
	SHELL_G_SCB = 0x11,
	SHELL_G_STP = 0x12,
	SHELL_G_STS = 0x13,
	SHELL_G_SCL = 0x14,
	SHELL_G_SCQ = 0x15,
	SHELL_G_SSP = 0x16,
	SHELL_G_SPD = 0x17,
	SHELL_G_SDM = 0x18,
	DISPEL_G_SCB = 0x19,
	DISPEL_G_STP = 0x1A,
	DISPEL_G_STS = 0x1B,
	DISPEL_G_SCL = 0x1C,
	DISPEL_G_SCQ = 0x1D,
	DISPEL_G_SSP = 0x1E,
	DISPEL_G_SPD = 0x1F,
	DISPEL_G_SDM = 0x20,
	AERORA_G_R = 0x21,
	AERORA_G_L = 0x22,
	AEROGA_G_R = 0x23,
	AEROGA_G_L = 0x24,
	TORNADO_G_R = 0x25,
	TORNADO_G_L = 0x26,
	FLOAT_G_R = 0x27,
	FLOAT_G_L = 0x28,
	AERO_G_R = 0x29,
	AERO_G_L = 0x2A,
	AERO_G_C = 0x2B,
	DRAIN_G_R = 0x2C,
	DRAIN_G_L = 0x2D,
	OSMOSE_G_R = 0x2E,
	OSMOSE_G_L = 0x2F,
	TRANSFORM_G = 0x30,
	WARP_G = 0x31,
	SCAN_G_PART = 0x32,
	SCAN_G_FULL = 0x33,
	HASTE_G = 0x34,
	HASTE2_G_ = 0x35,
	SHIELD_G = 0x36,
	SHIELD2_G = 0x37,
	ESUNA_G_CIRCLE = 0x38,
	ESUNA_G_SQUARE = 0x39,
	THUNDER_G = 0x3A,
	THUNDARA_G = 0x3B,
	THUNDAGA_G = 0x3C,
	COMET_G = 0x3D,
	METEOR_G = 0x3E,
	ULTIMA_G = 0x3F,
	SPRAY = 0x40,
	PALETTE = 0x41,
	SYS_UP1 = 0x42,
	SYS_UP2 = 0x43,
	COM_LV1 = 0x44,
	COM_LV2 = 0x45,
	COM_LV3 = 0x46,
	KINGDOM = 0x47,
	HYPERION = 0x48,
	GEPETTO = 0x49,
	CID = 0x4A,
	LEON = 0x4B,
	YUFFIE = 0x4C,
	AERITH = 0x4D,
	CACTUAR = 0x4E,
	CHOCOBO = 0x4F,
	CINDY = 0x50,
	SHIVA = 0x51,
	LAMIA = 0x52,
	SANDY = 0x53,
	SYLPH = 0x54,
	CARBUNCLE = 0x55,
	MINDY = 0x56,
	GOBLIN = 0x57,
	BOMB = 0x58,
	REMORA = 0x59,
	AHRIMAN = 0x5A,
	IMP = 0x5B,
	SIREN = 0x5C,
	STINGRAY = 0x5D,
	CATOBLEPAS = 0x5E,
	ADAMANT = 0x5F,
	SERPENT = 0x60,
	IFRIT = 0x61,
	ODIN = 0x62,
	ATOMOS = 0x63,
	GOLEM = 0x64,
	DIABLOS = 0x65,
	DEATHGUISE = 0x66,
	TYPHOON = 0x67,
	ALEXANDER = 0x68,
	LEVIATHAN = 0x69,
	RAMUH = 0x6A,
	OMEGA = 0x6B,
	MOOGLES = 0x6C,
	VALEFOR = 0x6D,
	PUPU = 0x6E,
	CERBERUS = 0x6F,
	TONBERRY = 0x70,
	PANDAEMONIUM = 0x71,
	IXION = 0x72,
	GILGAMESH = 0x73,
	PHOENIX = 0x74,
	EDEN = 0x75,
	BAHAMUT = 0x76,
	// 0x77 - 0x7F unused
	WHEEL_G = 0x80,
	FANG_G = 0x81,
	HORN_G = 0x82,
	ANGEL_G = 0x83,
	DARK_G = 0x84,
	SHOES_G = 0x85,
	ROCK_G_R = 0x86,
	ROCK_G_L = 0x87,
	SCISSORS_G_R = 0x88,
	SCISSORS_G_L = 0x89,
	PAPER_G_R = 0x8A,
	PAPER_G_L = 0x8B,
	CROWN_G = 0x8C,
	DRILL_G = 0x8D,
	CATERPILLAR_G_R = 0x8E,
	CATERPILLAR_G_SQUARE = 0x8F,
	// 0x90 - 0x9F unused
};

enum KHGummiType {
	EXTRA,		// 0x00: garage upgrades, blueprints etc.
	COCKPIT,	// 0x01
	ENGINE,		// 0x02
	ARMOR_1,	// 0x03
	ARMOR_2,	// 0x04
	ARMOR_3,	// 0x05
	WING,		// 0x06
	SPECIAL,	// 0x07
	WEAPON,		// 0x08
	DESIGN,		// 0x09 Special Final Mix Gummis
};

struct KHGummiStats {
	char identifier[4];			// 0x00
	uint8_t type_id;			// 0x04
	uint8_t id;					// 0x05

	uint8_t unknown_1;			// Seems to always be gummi_id + 0xA0, but it is unknown why.

	uint8_t size;				// 0x07
	uint8_t garage_id;			// 0x08: Like the gummi_id, but skips gummi blocks which are not used for building (KHGummiType = NONE -> gummi_garage_id = 0xFF)
	uint8_t special_id;			// 0x09: Unknown id only used by drain, osmose, warp and scan gummi blocks, others are 0xFF

	uint8_t unknown_2;			// 0x0A: 0x01 for engine, warp, haste, shield, esuna and weapon gummi blocks, others are 0x00

	uint8_t limit;				// 0x0B
	uint8_t min_speed;			// 0x0C: Both speed variables are used as handling for wing gummi blocks
	uint8_t max_speed;			// 0x0D 
	uint8_t horsepower;			// 0x0E

	uint8_t unknown_3[3];

	uint16_t damage;			// 0x12
	uint16_t price_sell;		// 0x14
	uint16_t price_buy;			// 0x16
	float armor;				// 0x18
};

struct KHGummi {
	KHGummiStats *stats;
	uint8_t *name_address;
	int name_length;
	uint8_t *description_address;
	int description_length;
};