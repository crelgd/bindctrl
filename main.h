/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#pragma once

#include "ViGEm/Client.h"

#define DIRECTION_SIZE	1024

#define HHOOK_PATH		"pdevEvent.dll"
#define HHOOK_KEYBOARD	"_EventKeyboardCheck@12"

#define PIPE_CHANNEL_NAME L"\\\\.\\pipe\\CRELGD_PDEVHOOK"
#define PIPE_SIZE		  1024	

LRESULT WINAPI EventKeyboardCheck(int code, WPARAM wParam, LPARAM lParam);

class vigemDriver
{
public:
	vigemDriver();
	~vigemDriver();

	XINPUT_STATE xState;

private:
	PVIGEM_CLIENT dClient;
	VIGEM_ERROR dConnection;
	PVIGEM_TARGET hPad;
	int addBusf;
};

class _Hook
{
public:
	_Hook(wchar_t* hmPath, int pathSize);
	~_Hook();

	void Keyboard();

private:
	HMODULE hHook;
	wchar_t* hmPathc;
	HOOKPROC hpKeyboard;
	HHOOK HookQueueKeyboard;
};

class _Pipe
{
public:
	_Pipe();
	~_Pipe();

private:
	HANDLE NamedPipe;
};

void FilePathNearbyMain(
	char* dst,
	size_t dstSizeInByte,
	const char* fileName,
	size_t fnSizeInByte
);

int ConvertWSTR(char* in, wchar_t* out, int wcharLen);

extern HANDLE pipe;