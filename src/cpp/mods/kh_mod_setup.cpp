#include "kh_mod.h"

// Define metadata variables
string mod_name = "Mod Setup";
string mod_author = "HydroSulphide";
string mod_description = "This is a setup mod, that is loaded and executed before any other mod.";
string mod_version = "0.1";

extern "C" __declspec(dllexport) void __cdecl on_init() {
	print("Initializing Mod Setup ...");
}