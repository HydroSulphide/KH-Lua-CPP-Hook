#include "config.h"

#include <toml++/toml.h>

#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

Config Config::load(const fs::path &path) {
	Config config;
	auto data = toml::parse_file(path.u8string());

	for (const auto &[k, _] : data) {
		const auto &entry = data[k];

		const auto scripts = entry["scripts"].as_array();
		const auto base = entry["base"].value<std::uintptr_t>();
		const auto exe = entry["exe"].value<std::u8string>();
		const auto game_docs = entry["game_docs"].value<std::u8string>();

		if (!scripts) {
			throw std::runtime_error{std::string{k} + ": scripts failed to parse"};
		}
		if (!exe) {
			throw std::runtime_error{std::string{k} + ": exe failed to parse"};
		}
		if (!game_docs) {
			throw std::runtime_error{std::string{k} + ": game_docs failed to parse"};
		}

		std::vector<ScriptPath> paths;
		for (std::size_t i = 0; i < scripts->size(); i++) {
			const auto &v = *scripts->get_as<toml::table>(i);
			const auto str = v["path"].value<std::u8string>();
			const auto relative = v["relative"].value<bool>();

			if (!str) {
				throw std::runtime_error{std::string{k} + ": at index " + std::to_string(i) + ": script entry path failed to parse"};
			}
			if (!relative) {
				throw std::runtime_error{std::string{k} + ": at index " + std::to_string(i) + ": script entry relative failed to parse"};
			}

			paths.emplace_back(*str, *relative);
		}

		config.infos.emplace(*exe, GameInfo{.base_address = base.value_or(0), .script_paths = std::move(paths), .game_docs_path_string = *game_docs});
	}

	return config;
}

std::optional<std::reference_wrapper<const GameInfo>> Config::game_info(const std::u8string &exe) const {
	if (auto info = infos.find(exe); info != infos.end()) {
		return std::cref(info->second);
	} else {
		return {};
	}
}
