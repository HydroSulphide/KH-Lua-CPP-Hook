#include "kh_characters.h"

#include <format>

CharacterStats *sora_character_stats = nullptr;
CharacterStats *donald_character_stats = nullptr;
CharacterStats *goofy_character_stats = nullptr;

void character_stats_init(uintptr_t base_address, uintptr_t offset_sora, uintptr_t offset_donald, uintptr_t offset_goofy) {
	sora_character_stats = reinterpret_cast<CharacterStats *>(base_address + offset_sora);
	donald_character_stats = reinterpret_cast<CharacterStats *>(base_address + offset_donald);
	goofy_character_stats = reinterpret_cast<CharacterStats *>(base_address + offset_goofy);
}

FieldStats *sora_field_stats = nullptr;
FieldStats *donald_field_stats = nullptr;
FieldStats *goofy_field_stats = nullptr;

void field_stats_init(uintptr_t base_address, uintptr_t offset_sora, uintptr_t offset_donald, uintptr_t offset_goofy) {
	sora_field_stats = reinterpret_cast<FieldStats *>(base_address + offset_sora);
	donald_field_stats = reinterpret_cast<FieldStats *>(base_address + offset_donald);
	goofy_field_stats = reinterpret_cast<FieldStats *>(base_address + offset_goofy);
}

extern "C" __declspec(dllexport) CharacterStats *get_sora_character_stats() {
	return sora_character_stats;
}

extern "C" __declspec(dllexport) CharacterStats *get_donald_character_stats() {
	return donald_character_stats;
}

extern "C" __declspec(dllexport) CharacterStats *get_goofy_character_stats() {
	return goofy_character_stats;
}

extern "C" __declspec(dllexport) FieldStats *get_sora_field_stats() {
	return sora_field_stats;
}

extern "C" __declspec(dllexport) FieldStats *get_donald_field_stats() {
	return donald_field_stats;
}

extern "C" __declspec(dllexport) FieldStats *get_goofy_field_stats() {
	return goofy_field_stats;
}