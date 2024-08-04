#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "input.h"
#include "lua_exec.h"

bool requested_reset = false;
bool show_console = true;

bool key_pressed_F1 = false;
bool key_pressed_F2 = false;
bool key_pressed_F3 = false;

void handle_input() {
	if (requested_reset == false) {
		if (GetAsyncKeyState(VK_F3) & 0x8000) {
			if (!key_pressed_F3) {
				switch (lua_backend->frame_limit) {
				case 16:
					lua_backend->frame_limit = 8;
					print_message("Frequency set to 120Hz.\n", MESSAGE_DEFAULT);
					break;
				case 8:
					lua_backend->frame_limit = 4;
					print_message("Frequency set to 240Hz.\n", MESSAGE_DEFAULT);
					break;
				case 4:
					lua_backend->frame_limit = 16;
					print_message("Frequency set to 60Hz.\n", MESSAGE_DEFAULT);
					break;
				}
			}
			key_pressed_F3 = true;
		} else {
			key_pressed_F3 = false;
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000) {
			if (!key_pressed_F2) {
				if (show_console) {
					ShowWindow(GetConsoleWindow(), SW_HIDE);
					show_console = false;
				}

				else {
					ShowWindow(GetConsoleWindow(), SW_RESTORE);
					show_console = true;
				}
			}
			key_pressed_F2 = true;
		} else {
			key_pressed_F2 = false;
		}

		if (GetAsyncKeyState(VK_F1) & 0x8000) {
			if (!key_pressed_F1) {
				requested_reset = true;
			}
			key_pressed_F1 = true;
		} else {
			key_pressed_F1 = false;
		}
	} else {
		reset_lua();
		requested_reset = false;
	}
}