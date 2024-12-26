#include "kh_mod.h"

// Define metadata variables
string mod_name = "Example Mod";
string mod_author = "HydroSulphide";
string mod_description = "This is a description of Example Mod.";
string mod_version = "1.0.0";

KH_MOD on_init() {
	print_line("on_init()");
}

KH_MOD on_frame() {
	print_line("on_frame()");
}

KH_MOD on_get_reward(DWORD64 reward_id) {
	print_line("on_get_reward()");
}

KH_MOD on_get_hit() {
	print_line("on_get_hit()");
}