/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#define PDEV_EXPORTS
#include <format>
#include "main.h"

LRESULT WINAPI EventKeyboardCheck(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);

	switch (code)
	{
	case HC_ACTION:
		{
			KBDLLHOOKSTRUCT* kdb = (KBDLLHOOKSTRUCT*) lParam;

			DWORD vk = kdb->vkCode;

			DWORD wData;

			WriteFile(pipe, &vk, sizeof(vk), &wData, NULL);

			OutputDebugStringA(std::format("Writed {}\n", vk).c_str());
		}
		break;
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}
