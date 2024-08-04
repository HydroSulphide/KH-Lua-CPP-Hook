#pragma once

#include <filesystem>

bool api_init_cpp(uintptr_t base_address, const std::filesystem::path &path);
void load_mod_setup_cpp();
void load_mods_cpp();
void on_frame_cpp();