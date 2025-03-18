#include "kh_font.h"
#include "console_lib.h"

#include <unordered_map>

const std::unordered_map<wchar_t, uint8_t> kh_to_c = {
	{L' ', 0x1},
	{L'\n', 0x2},
	{L'▮', 0x20},
	{L'0', 0x21},
	{L'1', 0x22},
	{L'2', 0x23},
	{L'3', 0x24},
	{L'4', 0x25},
	{L'5', 0x26},
	{L'6', 0x27},
	{L'7', 0x28},
	{L'8', 0x29},
	{L'9', 0x2A},
	{L'A', 0x2B},
	{L'B', 0x2C},
	{L'C', 0x2D},
	{L'D', 0x2E},
	{L'E', 0x2F},
	{L'F', 0x30},
	{L'G', 0x31},
	{L'H', 0x32},
	{L'I', 0x33},
	{L'J', 0x34},
	{L'K', 0x35},
	{L'L', 0x36},
	{L'M', 0x37},
	{L'N', 0x38},
	{L'O', 0x39},
	{L'P', 0x3A},
	{L'Q', 0x3B},
	{L'R', 0x3C},
	{L'S', 0x3D},
	{L'T', 0x3E},
	{L'U', 0x3F},
	{L'V', 0x40},
	{L'W', 0x41},
	{L'X', 0x42},
	{L'Y', 0x43},
	{L'Z', 0x44},
	{L'a', 0x45},
	{L'b', 0x46},
	{L'c', 0x47},
	{L'd', 0x48},
	{L'e', 0x49},
	{L'f', 0x4A},
	{L'g', 0x4B},
	{L'h', 0x4C},
	{L'i', 0x4D},
	{L'j', 0x4E},
	{L'k', 0x4F},
	{L'l', 0x50},
	{L'm', 0x51},
	{L'n', 0x52},
	{L'o', 0x53},
	{L'p', 0x54},
	{L'q', 0x55},
	{L'r', 0x56},
	{L's', 0x57},
	{L't', 0x58},
	{L'u', 0x59},
	{L'v', 0x5A},
	{L'w', 0x5B},
	{L'x', 0x5C},
	{L'y', 0x5D},
	{L'z', 0x5E},
	{L'!', 0x5F},
	{L'?', 0x60},
	{L'&', 0x61},
	{L'%', 0x62},
	{L'+', 0x63},
	{L'-', 0x64},
	{L'×', 0x65},
	{L'/', 0x66},
	{L'*', 0x67},
	{L'.', 0x68},
	{L',', 0x69},
	{L'•', 0x6A},
	{L':', 0x6B},
	{L';', 0x6C},
	{L'…', 0x6D},
	{L'−', 0x6E},
	{L'–', 0x6F},
	{L'~', 0x70},
	{L'\'', 0x71},
	{L'“', 0x72},
	{L'„', 0x73},
	{L'(', 0x74},
	{L')', 0x75},
	{L'[', 0x76},
	{L']', 0x77},
	{L'〈', 0x78},
	{L'⟩', 0x79},
	{L'★', 0x7A},
	{L'☆', 0x7B},
	{L'↑', 0x7C},
	{L'↓', 0x7D},
	{L'→', 0x7E},
	{L'←', 0x7F},
	{L'●', 0x80},
	{L'■', 0x81},
	// Special Symbols
	{L'\uE000', 0x82}, // KH_SYMBOL_BATTLE_CONSUMABLE
	{L'\uE001', 0x83}, // KH_SYMBOL_MENU_CONSUMABLE
	{L'\uE002', 0x84}, // KH_SYMBOL_OTHER_ITEM
	{L'\uE003', 0x85}, // KH_SYMBOL_ABILITY_STARS
	{L'\uE004', 0x86}, // KH_SYMBOL_KEYBLADE
	{L'\uE005', 0x87}, // KH_SYMBOL_STAFF
	{L'\uE006', 0x88}, // KH_SYMBOL_SHIELD
	{L'\uE007', 0x89}, // KH_SYMBOL_ACCESSORY
	{L'\uE008', 0x8A}, // KH_SYMBOL_MAGIC
	{L'\uE009', 0x8B}, // KH_SYMBOL_MICKEY_MOUSE
	{L'\uE00A', 0x8C}, // KH_SYMBOL_PS_CIRCLE
	{L'\uE00B', 0x8D}, // KH_SYMBOL_PS_CROSS
	{L'\uE00C', 0x8E}, // KH_SYMBOL_PS_TRIANGLE
	{L'\uE00D', 0x8F}, // KH_SYMBOL_PS_SQUARE
	{L'▲', 0x90},
	{L'▼', 0x91},
	{L'▶', 0x92},
	{L'◀', 0x93},
	// Gummi Symbols
	{L'\uE00E', 0x94}, // KH_SYMBOL_GUMMI_SCP
	{L'\uE00F', 0x95}, // KH_SYMBOL_GUMMI_STP
	{L'\uE010', 0x96}, // KH_SYMBOL_GUMMI_STS
	{L'\uE011', 0x97}, // KH_SYMBOL_GUMMI_SCL
	{L'\uE012', 0x98}, // KH_SYMBOL_GUMMI_SCQ
	{L'\uE013', 0x99}, // KH_SYMBOL_GUMMI_SSP
	{L'\uE014', 0x9A}, // KH_SYMBOL_GUMMI_SPD
	{L'\uE015', 0x9B}, // KH_SYMBOL_GUMMI_SDM
	{L'\uE016', 0x9C}, // KH_SYMBOL_GUMMI_SCAN_PART
	{L'\uE017', 0x9D}, // KH_SYMBOL_GUMMI_SCAN_FULL
	{L'▢', 0x9E},
	// Big Digits
	{L'\uE018', 0x9F}, // KH_SYMBOL_BIG_DIGIT_1
	{L'\uE019', 0xA0}, // KH_SYMBOL_BIG_DIGIT_2
	{L'\uE01A', 0xA1}, // KH_SYMBOL_BIG_DIGIT_3
	{L'\uE01B', 0xA2}, // KH_SYMBOL_BIG_DIGIT_4
	{L'\uE01C', 0xA3}, // KH_SYMBOL_BIG_DIGIT_5
	{L'\uE01D', 0xA4}, // KH_SYMBOL_BIG_DIGIT_6
	{L'\uE01E', 0xA5}, // KH_SYMBOL_BIG_DIGIT_7
	{L'\uE01F', 0xA6}, // KH_SYMBOL_BIG_DIGIT_8
	{L'\uE020', 0xA7}, // KH_SYMBOL_BIG_DIGIT_9
	{L'⋯', 0xA8},
	{L'®', 0xA9},
	{L'Ⅲ', 0xC4},
	{L'Ⅶ', 0xC5},
	{L'Ⅷ', 0xC6},
	{L'Ⅹ', 0xC7},
	{L'Œ', 0xC8},
	{L'æ', 0xC9},
	{L'¡', 0xCA},
	{L'¿', 0xCB},
	{L'À', 0xCC},
	{L'Á', 0xCD},
	{L'Â', 0xCE},
	{L'Ä', 0xCF},
	{L'Ç', 0xD0},
	{L'È', 0xD1},
	{L'É', 0xD2},
	{L'Ê', 0xD3},
	{L'Ë', 0xD4},
	{L'Ì', 0xD5},
	{L'Í', 0xD6},
	{L'Î', 0xD7},
	{L'Ï', 0xD8},
	{L'Ñ', 0xD9},
	{L'Ò', 0xDA},
	{L'Ó', 0xDB},
	{L'Ô', 0xDC},
	{L'Ö', 0xDD},
	{L'Ù', 0xDE},
	{L'Ú', 0xDF},
	{L'Û', 0xE0},
	{L'Ü', 0xE1},
	{L'ß', 0xE2},
	{L'à', 0xE3},
	{L'á', 0xE4},
	{L'â', 0xE5},
	{L'ä', 0xE6},
	{L'ç', 0xE7},
	{L'è', 0xE8},
	{L'é', 0xE9},
	{L'ê', 0xEA},
	{L'ë', 0xEB},
	{L'ì', 0xEC},
	{L'í', 0xED},
	{L'î', 0xEE},
	{L'ï', 0xEF},
	{L'ñ', 0xF0},
	{L'ò', 0xF1},
	{L'ó', 0xF2},
	{L'ô', 0xF3},
	{L'ö', 0xF4},
	{L'ù', 0xF5},
	{L'ú', 0xF6},
	{L'û', 0xF7},
	{L'ü', 0xF8},
	{L'°', 0xF9},
	{L'—', 0xFA},
	{L'»', 0xFB},
	{L'«', 0xFC},
	{L'\uE021', 0x0F01} // KH_SYMBOL_NEW_PAGE
};

std::string to_kh_string(const std::wstring &input) {
	static std::vector<char> output;
	output.clear();

	for (wchar_t c : input) {
		auto it = kh_to_c.find(c);
		if (it != kh_to_c.end()) {
			unsigned short value = it->second;
			if (value > 0xFF) {
				// Handle multi-byte values (e.g., NEW_PAGE)
				output.push_back(static_cast<char>((value >> 8) & 0xFF)); // High byte
				output.push_back(static_cast<char>(value & 0xFF));		  // Low byte
			} else {
				// Handle single-byte values
				output.push_back(static_cast<char>(value));
			}
		} else {
			// If the character is not found, skip it or handle it as needed
			output.push_back(0x1); // Default to space
		}
	}

	// Add null terminator to make it a valid C-style string
	output.push_back('\0');

	return std::string(output.data());
}