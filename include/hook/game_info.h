#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

struct ScriptPath {
	std::u8string str;
	bool relative;
};

struct GameInfo {
	std::uintptr_t base_address;
	std::vector<ScriptPath> script_paths;
	std::u8string game_docs_path_string;
};
