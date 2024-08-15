#pragma once

#include <filesystem>

void update_loaded_gameobjects();
bool api_init_cpp(uint64_t base_address, const std::filesystem::path &path);
void load_mod_setup_cpp();
void load_mods_cpp();
void unload_mods_cpp();
void reload_mods_cpp();
void on_frame_cpp();