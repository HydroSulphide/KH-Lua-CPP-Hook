#pragma once

#include <filesystem>

bool api_init(uintptr_t base_address, const std::filesystem::path &path);

void on_frame_cpp();