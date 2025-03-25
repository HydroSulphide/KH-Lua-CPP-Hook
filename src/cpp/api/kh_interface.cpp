#include "kh_interface.h"
#include "kh_gameobject.h"
#include "kh_party.h"
#include "kh_inventory.h"
#include "kh_gummi.h"
#include "kh_font.h"
#include "kh_item.h"
#include "console_lib.h"
#include "memory_lib.h"

#include <format>

uintptr_t *loaded_gameobjects_start_pointer;
size_t max_loaded_gameobjects = 50;

std::vector<KHGameObject *> loaded_gameobjects;

KHParty *party;
KHGameObject *sora;
KHGameObject *donald;
KHGameObject *goofy;
KHGameObject *tarzan;
KHGameObject *aladdin;
KHGameObject *ariel;
KHGameObject *jack;
KHGameObject *peter_pan;
KHGameObject *beast;

KHAttributes *sora_attributes;
KHAttributes *donald_attributes;
KHAttributes *goofy_attributes;
KHAttributes *tarzan_attributes;
KHAttributes *aladdin_attributes;
KHAttributes *ariel_attributes;
KHAttributes *jack_attributes;
KHAttributes *peter_pan_attributes;
KHAttributes *beast_attributes;

KHInventory *inventory;

std::vector<KHGummi> gummis;
std::vector<KHItem> items;
uint64_t item_names_offset_address;

std::vector<KHStringRepoint> string_repoints;

bool is_skip_splash_screen = false;
uint8_t *splash_screen_done_flag;

void update_loaded_gameobject_addresses() {
	for (KHGameObject *obj : loaded_gameobjects)
		delete obj;
	loaded_gameobjects.clear();

	sora = nullptr;
	donald = nullptr;
	goofy = nullptr;
	tarzan = nullptr;
	aladdin = nullptr;
	ariel = nullptr;
	jack = nullptr;
	peter_pan = nullptr;
	beast = nullptr;

	for (size_t i = 0; i < max_loaded_gameobjects; i++) {
		uint64_t gameobject_address = *(loaded_gameobjects_start_pointer + i*5);
		if (gameobject_address != 0) {
			KHGameObject *gameobject_ptr = init_kh_gameobject(gameobject_address);
			if (gameobject_ptr) {
				//print_message_line(std::format("Object {:d}: 0x{:X}", i, gameobject_address));
				//print_message_line(std::format("\tModel {:X}: {}", reinterpret_cast<uint64_t>(gameobject_ptr->model), std::string(gameobject_ptr->model->name, 16)));
				loaded_gameobjects.push_back(gameobject_ptr);

				if (gameobject_ptr->model) {
					if (strcmp(gameobject_ptr->model->name, "SORA\0\0\0\0\0\0\0\0\0\0\0") == 0) { // std::string(gameobject_ptr->actor->name).compare(std::string("SORA")) == 0) {
						sora = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "DONALD\0\0\0\0\0\0\0\0\0") == 0) {
						donald = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "GOOFY\0\0\0\0\0\0\0\0\0\0") == 0) {
						goofy = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "TARZAN\0\0\0\0\0\0\0\0\0") == 0) {
						tarzan = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "ALADDIN\0\0\0\0\0\0\0\0") == 0) {
						aladdin = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "ARIEL\0\0\0\0\0\0\0\0\0\0") == 0) {
						ariel = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "JACK\0\0\0\0\0\0\0\0\0\0\0") == 0) {
						jack = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "PETERPAN\0\0\0\0\0\0\0") == 0) {
						peter_pan = gameobject_ptr;
					} else if (strcmp(gameobject_ptr->model->name, "BEAST\0\0\0\0\0\0\0\0\0\0") == 0) {
						beast = gameobject_ptr;
					}
				}
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

void init_kh_attributes(uint64_t sora_attr_addr, uint64_t donald_attr_addr, uint64_t goofy_attr_addr, uint64_t tarzan_attr_addr, uint64_t aladdin_attr_addr, uint64_t ariel_attr_addr, uint64_t jack_attr_addr, uint64_t peter_pan_attr_addr, uint64_t beast_attr_addr) {
	sora_attributes = reinterpret_cast<KHAttributes *>(sora_attr_addr);
	donald_attributes = reinterpret_cast<KHAttributes *>(donald_attr_addr);
	goofy_attributes = reinterpret_cast<KHAttributes *>(goofy_attr_addr);
	tarzan_attributes = reinterpret_cast<KHAttributes *>(tarzan_attr_addr);
	aladdin_attributes = reinterpret_cast<KHAttributes *>(aladdin_attr_addr);
	ariel_attributes = reinterpret_cast<KHAttributes *>(ariel_attr_addr);
	jack_attributes = reinterpret_cast<KHAttributes *>(jack_attr_addr);
	peter_pan_attributes = reinterpret_cast<KHAttributes *>(peter_pan_attr_addr);
	beast_attributes = reinterpret_cast<KHAttributes *>(beast_attr_addr);
}

void init_kh_gummis(std::vector<TOMLKHGummi> gummis_toml_data) {
	gummis.clear();
	for (const auto &gummi_toml_data : gummis_toml_data) {
		KHGummi gummi {
			reinterpret_cast<KHGummiStats *>(gummi_toml_data.stats_address),
			reinterpret_cast<uint8_t *>(gummi_toml_data.name_address),
			gummi_toml_data.name_length,
			reinterpret_cast<uint8_t *>(gummi_toml_data.description_address),
			gummi_toml_data.description_length
		};
		gummis.push_back(gummi);
	}
}

void init_kh_items(std::vector<TOMLKHItem> items_toml_data) {
	items.clear();
	for (const auto &item_toml_data : items_toml_data) {
		KHItem item {reinterpret_cast<KHItemStats *>(item_toml_data.item_stats_address), 
			reinterpret_cast<KHAccessoryStats *>(item_toml_data.accessory_stats_address), 
			reinterpret_cast<KHWeaponStats *>(item_toml_data.weapon_stats_address)
		};
		items.push_back(item);
	}
}

void init_kh_item_names_offset_address(uint64_t item_names_offset_addr) {
	item_names_offset_address = item_names_offset_addr;
}

void init_kh_item_names() {
	uint32_t *item_names_offset = reinterpret_cast<uint32_t *>(item_names_offset_address);
	uint8_t *item_names = reinterpret_cast<uint8_t *>(MemoryLib::get_4to8_pointer(*item_names_offset));

	for (size_t i = 1; i <= 0xFF; i++) {
		std::wstring item_name = kh_to_c_string(item_names);
		uint64_t item_name_address = reinterpret_cast<uint64_t>(item_names);

		items[i].name = reinterpret_cast<uint8_t *>(item_name_address);
		items[i].name_length = item_name.length();

		uint64_t description_address = MemoryLib::get_4to8_pointer(items[i].item_stats->description_pointer);
		items[i].description = reinterpret_cast<uint8_t *>(description_address);

		uint8_t *description_pointer = reinterpret_cast<uint8_t *>(description_address);
		size_t description_length = 0;
		while (*description_pointer) {
			description_length++;
			description_pointer++;
		}
		items[i].description_length = description_length;
		
		item_names += item_name.length() + 1;
	}
}

void init_kh_splash_screen_done_flag(uint64_t splash_screen_done_flag_address) {
	splash_screen_done_flag = reinterpret_cast<uint8_t *>(splash_screen_done_flag_address);
}

void on_splash_screen() {
	*(splash_screen_done_flag) = is_skip_splash_screen ? 1 : 0;
}

extern "C" __declspec(dllexport) KHGameObject **get_loaded_gameobjects(size_t *count) {
	*count = loaded_gameobjects.size();
	return loaded_gameobjects.data();
}

extern "C" __declspec(dllexport) KHParty *__cdecl get_party() {
	return party;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_sora() {
	return sora;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_donald() {
	return donald;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_goofy() {
	return goofy;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_tarzan() {
	return tarzan;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_aladdin() {
	return aladdin;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_ariel() {
	return ariel;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_jack() {
	return jack;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_peter_pan() {
	return peter_pan;
}

extern "C" __declspec(dllexport) KHGameObject *__cdecl get_beast() {
	return beast;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_sora_attributes() {
	return sora_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_donald_attributes() {
	return donald_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_goofy_attributes() {
	return goofy_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_tarzan_attributes() {
	return tarzan_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_aladdin_attributes() {
	return aladdin_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_ariel_attributes() {
	return ariel_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_jack_attributes() {
	return jack_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_peter_pan_attributes() {
	return peter_pan_attributes;
}

extern "C" __declspec(dllexport) KHAttributes *__cdecl get_beast_attributes() {
	return beast_attributes;
}

extern "C" __declspec(dllexport) KHInventory *__cdecl get_inventory() {
	return inventory;
}

extern "C" __declspec(dllexport) KHGummi *__cdecl get_gummis() {
	return gummis.data();
}

extern "C" __declspec(dllexport) KHItem *__cdecl get_items() {
	return items.data();
}

void set_new_string(const wchar_t *new_string, size_t old_string_length, uint8_t *string_address) {
	std::wstring new_wstring = new_string ? new_string : L"";
	std::string new_kh_string = c_to_kh_string(new_wstring);

	auto it = std::find_if(string_repoints.begin(), string_repoints.end(), [string_address](const KHStringRepoint &repoint) { return repoint.old_address == reinterpret_cast<uint64_t>(string_address); });

	if (new_wstring.size() <= old_string_length) {
		if (it != string_repoints.end()) {
			string_repoints.erase(it);
		}

		for (int i = 0; i < old_string_length; i++) {
			if (i < new_wstring.size()) {
				*(string_address + i) = new_kh_string[i];
			} else {
				*(string_address + i) = 0x00;
			}
		}
	} else {
		if (it != string_repoints.end()) {
			it->new_string = new_kh_string;
			return;
		}
		KHStringRepoint new_repoint = KHStringRepoint{reinterpret_cast<uint64_t>(string_address), new_kh_string};
		string_repoints.push_back(new_repoint);
	}
}

extern "C" __declspec(dllexport) void set_gummi_name(KHGummi *gummi, const wchar_t *new_name) {
	set_new_string(new_name, gummi->name_length, gummi->name);
}

extern "C" __declspec(dllexport) void set_gummi_description(KHGummi *gummi, const wchar_t *new_desc) {
	set_new_string(new_desc, gummi->description_length, gummi->description);
}

extern "C" __declspec(dllexport) void set_item_name(KHItem *item, const wchar_t *new_name) {
	set_new_string(new_name, item->name_length, item->name);
}

extern "C" __declspec(dllexport) void set_item_description(KHItem *item, const wchar_t *new_desc) {
	set_new_string(new_desc, item->description_length, item->description);
}

extern "C" __declspec(dllexport) void set_weapon_model(KHItem *item, const char *new_model_string) {
	if (item && item->weapon_stats) {
		strcpy_s(item->weapon_stats->model_name, new_model_string);
	}
}

extern "C" __declspec(dllexport) void skip_splash_screen(bool skip) {
	is_skip_splash_screen = skip;
}