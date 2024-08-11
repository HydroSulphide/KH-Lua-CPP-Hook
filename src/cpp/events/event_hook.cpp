#include "console_lib.h" // Assuming this is your custom logging library
#include <format>
#include <unordered_map>
#include <vector>
#include <windows.h>

struct HookInfo {
	uintptr_t target_address;	  // Address where the hook is installed
	uintptr_t trampoline_address; // Address of the trampoline
	void (*custom_logic)(CONTEXT *); // Custom logic to execute when the hook is hit
};

std::unordered_map<uintptr_t, HookInfo> hook_map;

void create_trampoline(HookInfo &hook, const std::vector<BYTE> &overwritten_instructions) {
	size_t trampoline_size = overwritten_instructions.size() + 12;
	hook.trampoline_address = reinterpret_cast<uintptr_t>(VirtualAlloc(nullptr, trampoline_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

	if (!hook.trampoline_address) {
		print_message_line("Failed to allocate memory for the trampoline.", MESSAGE_ERROR);
		return;
	}

	// Copy the original instructions to the trampoline
	memcpy(reinterpret_cast<void *>(hook.trampoline_address), overwritten_instructions.data(), overwritten_instructions.size());

	BYTE *trampoline_instructions = reinterpret_cast<BYTE *>(hook.trampoline_address + overwritten_instructions.size());

	// Save RAX
	trampoline_instructions[0] = 0x50; // PUSH RAX

	// MOV RAX, <jump_address>
	trampoline_instructions[1] = 0x48;
	trampoline_instructions[2] = 0xB8;
	uintptr_t jump_address = hook.target_address + 1; // Jump to POP RAX (INT 3 + POP RAX)
	*reinterpret_cast<uintptr_t *>(trampoline_instructions + 3) = jump_address;

	// JMP RAX
	trampoline_instructions[11] = 0xFF;
	trampoline_instructions[12] = 0xE0;

	print_message_line(std::format("Trampoline installed at: 0x{:X}", hook.trampoline_address), MESSAGE_NONE);
}

LONG WINAPI custom_code_handler(EXCEPTION_POINTERS *pExceptionInfo) {
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) {
		uintptr_t exception_address = pExceptionInfo->ContextRecord->Rip;

		// Lookup the hook in the map
		auto it = hook_map.find(exception_address);
		if (it != hook_map.end()) {
			HookInfo &hook = it->second;
			print_message_line(std::format("Breakpoint hit at address: 0x{:X}", exception_address), MESSAGE_NONE);

			// Execute the custom logic
			if (hook.custom_logic) {
				hook.custom_logic(pExceptionInfo->ContextRecord);
			}

			// Redirect to the trampoline
			pExceptionInfo->ContextRecord->Rip = hook.trampoline_address;

			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

void install_event_hook(uintptr_t base_address, uint32_t event_offset, size_t overwritten_instructions_size, void (*custom_logic)(CONTEXT*)) {
	HookInfo hook;
	hook.target_address = base_address + event_offset;
	hook.custom_logic = custom_logic;

	// Save the original bytes
	std::vector<BYTE> overwritten_instructions(overwritten_instructions_size);
	DWORD old_protect;
	VirtualProtect((void *)hook.target_address, overwritten_instructions_size, PAGE_EXECUTE_READWRITE, &old_protect);
	memcpy(overwritten_instructions.data(), (void *)hook.target_address, overwritten_instructions_size);

	// Install the exception handler if not already installed
	static bool handler_installed = false;
	if (!handler_installed) {
		HANDLE handler = AddVectoredExceptionHandler(1, custom_code_handler);
		if (!handler) {
			print_message_line("Failed to add vectored exception handler.", MESSAGE_ERROR);
			return;
		}
		handler_installed = true;
	}

	// Overwrite the target address with INT 3 and POP RAX
	VirtualProtect((void *)hook.target_address, 2, PAGE_EXECUTE_READWRITE, &old_protect);
	*reinterpret_cast<BYTE *>(hook.target_address) = 0xCC;	   // INT 3
	*reinterpret_cast<BYTE *>(hook.target_address + 1) = 0x58; // POP RAX
	for (size_t i = 2; i < overwritten_instructions_size; i++) {
		*reinterpret_cast<BYTE *>(hook.target_address + i) = 0x90;
	}
	VirtualProtect((void *)hook.target_address, overwritten_instructions_size, old_protect, &old_protect);

	create_trampoline(hook, overwritten_instructions);

	// Store the hook information in the map
	hook_map[hook.target_address] = hook;

	print_message_line(std::format("Event hook installed at address: 0x{:X}", hook.target_address), MESSAGE_NONE);
}