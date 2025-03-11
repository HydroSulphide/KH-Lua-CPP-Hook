#pragma once

#include <cstdint>

struct KHSharedAbilities {
	uint8_t slot_1;
	uint8_t slot_2;
	uint8_t slot_3;
	uint8_t slot_4;
	uint8_t slot_5;
	uint8_t slot_6;
	uint8_t slot_7;
	uint8_t slot_8;
	uint8_t slot_9;
	uint8_t slot_10;
	uint8_t slot_11;
	uint8_t slot_12;
	uint8_t slot_13;
	uint8_t slot_14;
	uint8_t slot_15;
	uint8_t slot_16;
	uint8_t slot_17;
	uint8_t slot_18;
	uint8_t slot_19;
	uint8_t slot_20;
	uint8_t slot_21;
	uint8_t slot_22;
	uint8_t slot_23;
	uint8_t slot_24;
	uint8_t slot_25;
	uint8_t slot_26;
	uint8_t slot_27;
	uint8_t slot_28;
	uint8_t slot_29;
	uint8_t slot_30;
	uint8_t slot_31;
	uint8_t slot_32;
	uint8_t slot_33;
	uint8_t slot_34;
	uint8_t slot_35;
	uint8_t slot_36;
	uint8_t slot_37;
	uint8_t slot_38;
	uint8_t slot_39;
	uint8_t slot_40;
	uint8_t slot_41;
	uint8_t slot_42;
	uint8_t slot_43;
	uint8_t slot_44;
	uint8_t slot_45;
	uint8_t slot_46;
	uint8_t slot_47;
	uint8_t slot_48;
};

struct KHMagicTiers {
	uint8_t fire;
	uint8_t blizzard;
	uint8_t thunder;
	uint8_t cure;
	uint8_t gravity;
	uint8_t stop;
	uint8_t aero;
};

// >= 0x08: AbilityID
enum KHLevelUpStat {
	LVLUP_NONE,
	LVLUP_MAX_HP,
	LVLUP_MAX_MP,
	LVLUP_MAX_AP,
	LVLUP_STRENGTH,
	LVLUP_DEFENSE,
	LVLUP_MAX_ITEMS,
	LVLUP_MAX_ACCESSORIES,
};

struct KHLevelUpStatTable {
	uint8_t lvl_0;
	uint8_t lvl_1;
	uint8_t lvl_2;
	uint8_t lvl_3;
	uint8_t lvl_4;
	uint8_t lvl_5;
	uint8_t lvl_6;
	uint8_t lvl_7;
	uint8_t lvl_8;
	uint8_t lvl_9;
	uint8_t lvl_10;
	uint8_t lvl_11;
	uint8_t lvl_12;
	uint8_t lvl_13;
	uint8_t lvl_14;
	uint8_t lvl_15;
	uint8_t lvl_16;
	uint8_t lvl_17;
	uint8_t lvl_18;
	uint8_t lvl_19;
	uint8_t lvl_20;
	uint8_t lvl_21;
	uint8_t lvl_22;
	uint8_t lvl_23;
	uint8_t lvl_24;
	uint8_t lvl_25;
	uint8_t lvl_26;
	uint8_t lvl_27;
	uint8_t lvl_28;
	uint8_t lvl_29;
	uint8_t lvl_30;
	uint8_t lvl_31;
	uint8_t lvl_32;
	uint8_t lvl_33;
	uint8_t lvl_34;
	uint8_t lvl_35;
	uint8_t lvl_36;
	uint8_t lvl_37;
	uint8_t lvl_38;
	uint8_t lvl_39;
	uint8_t lvl_40;
	uint8_t lvl_41;
	uint8_t lvl_42;
	uint8_t lvl_43;
	uint8_t lvl_44;
	uint8_t lvl_45;
	uint8_t lvl_46;
	uint8_t lvl_47;
	uint8_t lvl_48;
	uint8_t lvl_49;
	uint8_t lvl_50;
	uint8_t lvl_51;
	uint8_t lvl_52;
	uint8_t lvl_53;
	uint8_t lvl_54;
	uint8_t lvl_55;
	uint8_t lvl_56;
	uint8_t lvl_57;
	uint8_t lvl_58;
	uint8_t lvl_59;
	uint8_t lvl_60;
	uint8_t lvl_61;
	uint8_t lvl_62;
	uint8_t lvl_63;
	uint8_t lvl_64;
	uint8_t lvl_65;
	uint8_t lvl_66;
	uint8_t lvl_67;
	uint8_t lvl_68;
	uint8_t lvl_69;
	uint8_t lvl_70;
	uint8_t lvl_71;
	uint8_t lvl_72;
	uint8_t lvl_73;
	uint8_t lvl_74;
	uint8_t lvl_75;
	uint8_t lvl_76;
	uint8_t lvl_77;
	uint8_t lvl_78;
	uint8_t lvl_79;
	uint8_t lvl_80;
	uint8_t lvl_81;
	uint8_t lvl_82;
	uint8_t lvl_83;
	uint8_t lvl_84;
	uint8_t lvl_85;
	uint8_t lvl_86;
	uint8_t lvl_87;
	uint8_t lvl_88;
	uint8_t lvl_89;
	uint8_t lvl_90;
	uint8_t lvl_91;
	uint8_t lvl_92;
	uint8_t lvl_93;
	uint8_t lvl_94;
	uint8_t lvl_95;
	uint8_t lvl_96;
	uint8_t lvl_97;
	uint8_t lvl_98;
	uint8_t lvl_99;
	uint8_t lvl_100;
};

// exp needed to get to this level (relative to current level)
struct KHLevelUpExpTable {
	uint16_t lvl_1;
	uint16_t lvl_2;
	uint16_t lvl_3;
	uint16_t lvl_4;
	uint16_t lvl_5;
	uint16_t lvl_6;
	uint16_t lvl_7;
	uint16_t lvl_8;
	uint16_t lvl_9;
	uint16_t lvl_10;
	uint16_t lvl_11;
	uint16_t lvl_12;
	uint16_t lvl_13;
	uint16_t lvl_14;
	uint16_t lvl_15;
	uint16_t lvl_16;
	uint16_t lvl_17;
	uint16_t lvl_18;
	uint16_t lvl_19;
	uint16_t lvl_20;
	uint16_t lvl_21;
	uint16_t lvl_22;
	uint16_t lvl_23;
	uint16_t lvl_24;
	uint16_t lvl_25;
	uint16_t lvl_26;
	uint16_t lvl_27;
	uint16_t lvl_28;
	uint16_t lvl_29;
	uint16_t lvl_30;
	uint16_t lvl_31;
	uint16_t lvl_32;
	uint16_t lvl_33;
	uint16_t lvl_34;
	uint16_t lvl_35;
	uint16_t lvl_36;
	uint16_t lvl_37;
	uint16_t lvl_38;
	uint16_t lvl_39;
	uint16_t lvl_40;
	uint16_t lvl_41;
	uint16_t lvl_42;
	uint16_t lvl_43;
	uint16_t lvl_44;
	uint16_t lvl_45;
	uint16_t lvl_46;
	uint16_t lvl_47;
	uint16_t lvl_48;
	uint16_t lvl_49;
	uint16_t lvl_50;
	uint16_t lvl_51;
	uint16_t lvl_52;
	uint16_t lvl_53;
	uint16_t lvl_54;
	uint16_t lvl_55;
	uint16_t lvl_56;
	uint16_t lvl_57;
	uint16_t lvl_58;
	uint16_t lvl_59;
	uint16_t lvl_60;
	uint16_t lvl_61;
	uint16_t lvl_62;
	uint16_t lvl_63;
	uint16_t lvl_64;
	uint16_t lvl_65;
	uint16_t lvl_66;
	uint16_t lvl_67;
	uint16_t lvl_68;
	uint16_t lvl_69;
	uint16_t lvl_70;
	uint16_t lvl_71;
	uint16_t lvl_72;
	uint16_t lvl_73;
	uint16_t lvl_74;
	uint16_t lvl_75;
	uint16_t lvl_76;
	uint16_t lvl_77;
	uint16_t lvl_78;
	uint16_t lvl_79;
	uint16_t lvl_80;
	uint16_t lvl_81;
	uint16_t lvl_82;
	uint16_t lvl_83;
	uint16_t lvl_84;
	uint16_t lvl_85;
	uint16_t lvl_86;
	uint16_t lvl_87;
	uint16_t lvl_88;
	uint16_t lvl_89;
	uint16_t lvl_90;
	uint16_t lvl_91;
	uint16_t lvl_92;
	uint16_t lvl_93;
	uint16_t lvl_94;
	uint16_t lvl_95;
	uint16_t lvl_96;
	uint16_t lvl_97;
	uint16_t lvl_98;
	uint16_t lvl_99;
	uint16_t lvl_100;
};

struct KHParty {
	KHSharedAbilities *shared_abilities;
	KHMagicTiers *magic_tiers;
	float *exp_multiplier;
	
	KHLevelUpStatTable *sora_lvlup_table;
	KHLevelUpStatTable *sora_lvlup_table_bonus_sword;
	KHLevelUpStatTable *sora_lvlup_table_bonus_shield;
	KHLevelUpStatTable *sora_lvlup_table_bonus_staff;
	KHLevelUpExpTable *sora_lvlup_exp_table_dusk;
	KHLevelUpExpTable *sora_lvlup_exp_table_midday;
	KHLevelUpExpTable *sora_lvlup_exp_table_dawn;

	KHLevelUpStatTable *donald_lvlup_table;
	KHLevelUpStatTable *donald_lvlup_table_bonus;
	KHLevelUpExpTable *donald_lvlup_exp_table;

	KHLevelUpStatTable *goofy_lvlup_table;
	KHLevelUpStatTable *goofy_lvlup_table_bonus;
	KHLevelUpExpTable *goofy_lvlup_exp_table;

	KHLevelUpStatTable *tarzan_lvlup_table;
	KHLevelUpStatTable *tarzan_lvlup_table_bonus;
	KHLevelUpExpTable *tarzan_lvlup_exp_table;

	KHLevelUpStatTable *aladdin_lvlup_table;
	KHLevelUpStatTable *aladdin_lvlup_table_bonus;
	KHLevelUpExpTable *aladdin_lvlup_exp_table;

	KHLevelUpStatTable *ariel_lvlup_table;
	KHLevelUpStatTable *ariel_lvlup_table_bonus;
	KHLevelUpExpTable *ariel_lvlup_exp_table;

	KHLevelUpStatTable *jack_lvlup_table;
	KHLevelUpStatTable *jack_lvlup_table_bonus;
	KHLevelUpExpTable *jack_lvlup_exp_table;

	KHLevelUpStatTable *peter_pan_lvlup_table;
	KHLevelUpStatTable *peter_pan_lvlup_table_bonus;
	KHLevelUpExpTable *peter_pan_lvlup_exp_table;

	KHLevelUpStatTable *beast_lvlup_table;
	KHLevelUpStatTable *beast_lvlup_table_bonus;
	KHLevelUpExpTable *beast_lvlup_exp_table;
};