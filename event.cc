/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#define PDEV_EXPORTS
#include <format>
#include "main.h"

InData iData;

LRESULT WINAPI EventKeyboardCheck(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* kdb;
	DWORD vk;

	switch (code)
	{
		case HC_ACTION:
		{
			if (wParam == WM_KEYDOWN) {
				kdb = (KBDLLHOOKSTRUCT*)lParam;
				vk = kdb->vkCode;

				iData.cK = vk;
				iData.read = false;

				XUSB_REPORT xu = {};
				xu.wButtons = XINPUT_GAMEPAD_A;

				if (iData.cK == 'W')
					vigem_target_x360_update(*iData.dClient, *iData.hPad, xu);
			}
			else {
				XUSB_REPORT xu = {};
				xu.wButtons = 0x0000;
				vigem_target_x360_update(*iData.dClient, *iData.hPad, xu);
			}
		}
		break;
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}
