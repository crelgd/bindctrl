/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "main.h"

_Hook::_Hook()
{
	// null
}

_Hook::~_Hook()
{
	UnhookWindowsHookEx(HookQueueKeyboard);
	// FreeLibrary(hDLL);
}

void _Hook::Keyboard(HINSTANCE hInstance)
{
	//hpKeyboard = (HOOKPROC)GetProcAddress(hHook, HHOOK_KEYBOARD);
	//if (!hpKeyboard) {
	////	FreeLibrary(hHook);
	//	throw runtime_error("keyboard func doesnt load");
	//}

	HookQueueKeyboard = SetWindowsHookEx(
		WH_KEYBOARD_LL,
		EventKeyboardCheck,
		hInstance,
		0
	);
	if (!HookQueueKeyboard) {
		//FreeLibrary(hHook);
		throw runtime_error("keyboard queue doesnt load");
	}
}
