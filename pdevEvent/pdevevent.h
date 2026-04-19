/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#pragma once

#ifdef PDEV_EXPORTS
#define _PDEV __declspec(dllexport)
#else
#define _PDEV __declspec(dllimport)
#endif

extern "C" {

_PDEV LRESULT WINAPI EventKeyboardCheck(int code, WPARAM wParam, LPARAM lParam);

}
extern HANDLE pipe;
