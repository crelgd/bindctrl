/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#pragma once

#include "ViGEm/Client.h"
#include "bindf.h"

#define DIRECTION_SIZE	1024
#define CONFIG_NAME	"config.conf"

//#define HHOOK_PATH		"pdevEvent.dll"
//#define HHOOK_KEYBOARD	"_EventKeyboardCheck@12"

//#define PIPE_CHANNEL_NAME L"\\\\.\\pipe\\CRELGD_PDEVHOOK"
//#define PIPE_SIZE		  1024	

LRESULT WINAPI EventKeyboardCheck(int code, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI EventMouseCheck(int code, WPARAM wParam, LPARAM lParam);

class vigemDriver
{
public:
	void Init();
	~vigemDriver();
	
	XINPUT_STATE xState;
	PVIGEM_TARGET hPad;
	PVIGEM_CLIENT dClient;

private:
	VIGEM_ERROR dConnection;
	int addBusf;
};

typedef struct InData_VD {
	DWORD cK = 0;
	bool read = true;
	PVIGEM_CLIENT* dClient;
	PVIGEM_TARGET* hPad;
	int pd_lines;
} InData;

extern InData iData;

class _Hook
{
public:
	_Hook();
	~_Hook();

	void Keyboard(HINSTANCE hInstance);
	void Mouse(HINSTANCE hInstance);

private:
	//HOOKPROC hpKeyboard;

	HHOOK HookQueueKeyboard;
	HHOOK HookQueueMouse;
};

/*
class _Pipe
{
public:
	void Init();
	~_Pipe();

private:
	HANDLE NamedPipe;
};
*/
/*
class Share
{
public:
	void Init();
	~Share();

private:
	HANDLE fMapping;
};
*/

void FilePathNearbyMain(
	char* dst,
	size_t dstSizeInByte,
	const char* fileName,
	size_t fnSizeInByte
);

int ConvertWSTR(char* in, wchar_t* out, int wcharLen);

DWORD SearchMouseKey(char sData);

extern ParseData* pd;
