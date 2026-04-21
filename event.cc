/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#define PDEV_EXPORTS
#include <format>
#include "main.h"

InData iData;

// ТУДУ сделать кароч конфиг с расладкой 
LRESULT WINAPI EventKeyboardCheck(int code, WPARAM wParam, LPARAM lParam)
{
	switch (code)
	{
	case HC_ACTION:
	{
		KBDLLHOOKSTRUCT* kdb;
		DWORD vk;

		XUSB_REPORT xu = {};

		if (wParam == WM_KEYDOWN) {
			kdb = (KBDLLHOOKSTRUCT*)lParam;
			vk = kdb->vkCode;

			iData.cK = vk;
			iData.read = false;

			xu.wButtons = xu.wButtons | XINPUT_GAMEPAD_A;

			int pd_size = iData.pd_lines;
			for (int i = 0; i < pd_size; i++) {
				if (kdb->vkCode == pd[i].btn) {
					xu.wButtons = pd[i].btnPad;
					vigem_target_x360_update(*iData.dClient, *iData.hPad, xu);
				}
			}
		}
		else {
			xu.wButtons = 0x0000;
			vigem_target_x360_update(*iData.dClient, *iData.hPad, xu);
		}
	}
	break;
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

LRESULT WINAPI EventMouseCheck(int code, WPARAM wParam, LPARAM lParam)
{
	int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;

	if (code == HC_ACTION)
	{
		MSLLHOOKSTRUCT* mouse = (MSLLHOOKSTRUCT*)lParam;
		XUSB_REPORT xu = {};

		switch (wParam) {
		case WM_MOUSEMOVE:
		{
			int x = (mouse->pt.x - centerX) * 300;
			int y = (mouse->pt.y - centerY) * 300;

			if (x > MAXSHORT) x = MAXSHORT-1;
			if (x < -(MAXSHORT)) x = -(MAXSHORT-1);
			if (y > MAXSHORT) y = -(MAXSHORT-1);
			if (y < -(MAXSHORT)) y = (MAXSHORT - 1);

			xu.sThumbRX = x;
			xu.sThumbRY = y;

			vigem_target_x360_update(*iData.dClient, *iData.hPad, xu);
		}
		break;

		case WM_LBUTTONDOWN:
		{

		}
		break;

		case WM_LBUTTONUP:
		{

		}
		break;

		case WM_RBUTTONDOWN:
		{

		}
		break;

		case WM_RBUTTONUP:
		{

		}
		break;
		}
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}