#pragma once

#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "game_info.h"

class Config {
  private:
	std::unordered_map<std::u8string, GameInfo> infos;

  public:
	static Config load(const std::filesystem::path &path);
	std::optional<std::reference_wrapper<const GameInfo>> gameInfo(const std::u8string &exe) const;
};
