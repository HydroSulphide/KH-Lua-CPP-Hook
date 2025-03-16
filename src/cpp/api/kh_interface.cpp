#include "kh_interface.h"
#include "kh_gameobject.h"
#include "kh_party.h"
#include "kh_inventory.h"
#include "console_lib.h"

#include <format>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 35;

std::vector<KHGameObject*> loaded_gameobjects;
KHGameObject *sora;

KHParty *party;
KHInventory *inventory;

void update_loaded_gameobject_addresses() {
	for (KHGameObject *obj : loaded_gameobjects)
		delete obj;
	loaded_gameobjects.clear();

	sora = nullptr;

	for (size_t i = 0; i < max_loaded_gameobjects; i++) {
		uint64_t gameobject_address = *(loaded_gameobjects_start_pointer + i);
		if (gameobject_address != 0) {
			KHGameObject *gameobject_ptr = init_kh_gameobject(gameobject_address);
			loaded_gameobjects.push_back(gameobject_ptr);

			if (gameobject_ptr->model && (strcmp(gameobject_ptr->model->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0)) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
				sora = gameobject_ptr;
			}
		}
	}
}

void init_kh_inventory(uint64_t item_stock_address, uint64_t gummi_stock_address, uint64_t munny_address) {
	delete inventory;
	inventory = new KHInventory{
		reinterpret_cast<KHItemStock *>(item_stock_address),
		reinterpret_cast<KHGummiStock *>(gummi_stock_address),
		reinterpret_cast<uint32_t *>(munny_address),
	};
}

void init_kh_party(uint64_t shared_abilities_address, uint64_t magic_tiers_address, uint64_t exp_multiplier_address, uint64_t lvlup_tables_address) {
	uint64_t sora_lvlup = lvlup_tables_address;
	uint64_t sora_lvlup_bonus_sword = sora_lvlup + 0x68; // levelup_table is 104 (0x68) bytes long
	uint64_t sora_lvlup_bonus_shield = sora_lvlup_bonus_sword + 0x68;
	uint64_t sora_lvlup_bonus_staff = sora_lvlup_bonus_shield + 0x68;
	uint64_t sora_lvlup_exp_dusk = sora_lvlup_bonus_staff + 0x68;
	uint64_t sora_lvlup_exp_midday = sora_lvlup_exp_dusk + 0xC8; // levelup_exp_table is 200 (0xC8) bytes long
	uint64_t sora_lvlup_exp_dawn = sora_lvlup_exp_midday + 0xC8;

	uint64_t donald_lvlup = sora_lvlup_exp_dawn + 0xC8;
	uint64_t donald_lvlup_bonus = donald_lvlup + 0x68;
	uint64_t donald_lvlup_exp = donald_lvlup_bonus + 0x68;

	uint64_t goofy_lvlup = donald_lvlup_exp + 0xC8;
	uint64_t goofy_lvlup_bonus = goofy_lvlup + 0x68;
	uint64_t goofy_lvlup_exp = goofy_lvlup_bonus + 0x68;

	uint64_t tarzan_lvlup = goofy_lvlup_exp + 0xC8;
	uint64_t tarzan_lvlup_bonus = tarzan_lvlup + 0x68;
	uint64_t tarzan_lvlup_exp = tarzan_lvlup_bonus + 0x68;

	uint64_t aladdin_lvlup = tarzan_lvlup_exp + 0xC8;
	uint64_t aladdin_lvlup_bonus = aladdin_lvlup + 0x68;
	uint64_t aladdin_lvlup_exp = aladdin_lvlup_bonus + 0x68;

	uint64_t ariel_lvlup = aladdin_lvlup_exp + 0xC8;
	uint64_t ariel_lvlup_bonus = ariel_lvlup + 0x68;
	uint64_t ariel_lvlup_exp = ariel_lvlup_bonus + 0x68;

	uint64_t jack_lvlup = ariel_lvlup_exp + 0xC8;
	uint64_t jack_lvlup_bonus = jack_lvlup + 0x68;
	uint64_t jack_lvlup_exp = jack_lvlup_bonus + 0x68;

	uint64_t peter_pan_lvlup = jack_lvlup_exp + 0xC8;
	uint64_t peter_pan_lvlup_bonus = peter_pan_lvlup + 0x68;
	uint64_t peter_pan_lvlup_exp = peter_pan_lvlup_bonus + 0x68;

	uint64_t beast_lvlup = peter_pan_lvlup_exp + 0xC8;
	uint64_t beast_lvlup_bonus = beast_lvlup + 0x68;
	uint64_t beast_lvlup_exp = beast_lvlup_bonus + 0x68;

	delete party;
	party = new KHParty{
		reinterpret_cast<KHSharedAbilities *>(shared_abilities_address), 
		reinterpret_cast<KHMagicTiers *>(magic_tiers_address),
		reinterpret_cast<float *>(exp_multiplier_address),

		reinterpret_cast<KHLevelUpStatTable *>(sora_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(sora_lvlup_bonus_sword), 
		reinterpret_cast<KHLevelUpStatTable *>(sora_lvlup_bonus_shield),
		reinterpret_cast<KHLevelUpStatTable *>(sora_lvlup_bonus_staff),
		reinterpret_cast<KHLevelUpExpTable *>(sora_lvlup_exp_dusk),
		reinterpret_cast<KHLevelUpExpTable *>(sora_lvlup_exp_midday),
		reinterpret_cast<KHLevelUpExpTable *>(sora_lvlup_exp_dawn),

		reinterpret_cast<KHLevelUpStatTable *>(donald_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(donald_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(donald_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(goofy_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(goofy_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(goofy_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(tarzan_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(tarzan_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(tarzan_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(aladdin_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(aladdin_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(aladdin_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(ariel_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(ariel_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(ariel_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(jack_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(jack_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(jack_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(peter_pan_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(peter_pan_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(peter_pan_lvlup_exp),

		reinterpret_cast<KHLevelUpStatTable *>(beast_lvlup),
		reinterpret_cast<KHLevelUpStatTable *>(beast_lvlup_bonus),
		reinterpret_cast<KHLevelUpExpTable *>(beast_lvlup_exp),
	};
}

extern "C" __declspec(dllexport) KHGameObject **get_loaded_gameobjects(size_t *count) {
	*count = loaded_gameobjects.size();
	return loaded_gameobjects.data();
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_sora() {
	return sora;
}

extern "C" __declspec(dllexport) KHParty *__cdecl get_party() {
	return party;
}

extern "C" __declspec(dllexport) KHInventory *__cdecl get_inventory() {
	return inventory;
}