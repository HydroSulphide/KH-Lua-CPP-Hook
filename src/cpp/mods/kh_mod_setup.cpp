#define KH_MOD_SETUP
#include "kh_mod.h"

// Define metadata variables
string mod_name = "Mod Setup";
string mod_author = "HydroSulphide";
string mod_description = "This is a setup mod, that is loaded and executed before any other mod.";
string mod_version = "0.1";

bool redirect_console_output() {
	FILE *p_console_output;
	if (freopen_s(&p_console_output, "CONOUT$", "w", stdout) != 0) {
		print("Failed to redirect stdout to console");
		return false;
	}
	if (freopen_s(&p_console_output, "CONOUT$", "w", stderr) != 0) {
		print("Failed to redirect stderr to console");
		return false;
	}
	return true;
}

extern "C" __declspec(dllexport) void __cdecl on_load() {
	redirect_console_output();
	print_metadata();
}

extern "C" __declspec(dllexport) void __cdecl on_init() {
	if (redirect_console_output()) {
		print("Redirected console output");
	}
}