#include "kh_mod.h"

// Define metadata variables
string mod_name = "Example Mod";
string mod_author = "HydroSulphide";
string mod_description = "This is a description of Example Mod.";
string mod_version = "1.0.0";

extern "C" __declspec(dllexport) void __cdecl on_init() {
	print("on_init()");
}

 extern "C" __declspec(dllexport) void __cdecl on_frame() {
     print("on_frame()");
 }