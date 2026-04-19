/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "main.h"

_Hook::_Hook(wchar_t* hmPath, int pathSize)
{
	//hHook = LoadLibraryW(hmPath);
	//if (!hHook) throw runtime_error("Hook loading err");
	hmPathc = hmPath;
}

_Hook::~_Hook()
{
	delete[] hmPathc;
	UnhookWindowsHookEx(HookQueueKeyboard);
	FreeLibrary(hHook);
}

void _Hook::Keyboard()
{
	//hpKeyboard = (HOOKPROC)GetProcAddress(hHook, HHOOK_KEYBOARD);
	//if (!hpKeyboard) {
	////	FreeLibrary(hHook);
	//	throw runtime_error("keyboard func doesnt load");
	//}

	HookQueueKeyboard = SetWindowsHookEx(
		WH_KEYBOARD_LL,
		EventKeyboardCheck,
		NULL,
		0
	);
	if (!HookQueueKeyboard) {
		FreeLibrary(hHook);
		throw runtime_error("keyboard queue doesnt load");
	}
}