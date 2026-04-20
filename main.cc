/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "main.h"
#include "bindf.h"

#include <string>
// #include <cstdio>

using namespace std;

HANDLE pipe;

/* эта хуйня прост для теста событий
void printAllBtns(vigemDriver* device)
{
	printf("%02X\n", device->xState.Gamepad.bLeftTrigger);
	printf("%02X\n", device->xState.Gamepad.bRightTrigger);
	printf("%02X\n", device->xState.Gamepad.sThumbLX);
	printf("%02X\n", device->xState.Gamepad.sThumbLY);
	printf("%02X\n", device->xState.Gamepad.sThumbRX);
	printf("%02X\n", device->xState.Gamepad.sThumbRY);
	printf("%02X\n", device->xState.Gamepad.wButtons);
}	
*/
// TODO: сделать кароч хук для отслеживаня событий
//		 и патом посылать сообщения в контролер
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	/* ne nado ved ne ispolzuyu dllku
	char hmPath[DIRECTION_SIZE] = { 0 };

	FilePathNearbyMain(hmPath, DIRECTION_SIZE, HHOOK_PATH, strlen(HHOOK_PATH));

	int hmPathSize = strlen(hmPath);

	wchar_t* ohmPath = new wchar_t[hmPathSize + 1];

	if (ConvertWSTR(hmPath, ohmPath, hmPathSize+1) != 0) {
		return 1;
	}
	*/ 

	_Hook hook;
	vigemDriver vd;
	BindF_File bff;

	try
	{
		char cmPath[DIRECTION_SIZE] = { 0 };

		FilePathNearbyMain(cmPath, DIRECTION_SIZE, CONFIG_NAME, strlen(CONFIG_NAME));

		string filename(cmPath);

		bff.ReadFile(filename);
		bff.Parse();

		hook.Keyboard(hInstance);
		vd.Init();

		iData.dClient = &vd.dClient;
		iData.hPad = &vd.hPad;
	}
	catch (runtime_error& err)
	{
		MessageBoxA(NULL, err.what(), "bindctlr err", 0);
		return 1;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void vigemDriver::Init()
{
	dClient = vigem_alloc();
	if (!dClient)
		throw runtime_error("ViGEm Client error");

	dConnection = vigem_connect(dClient); 
	if (!VIGEM_SUCCESS(dConnection)) {
		vigem_free(dClient);
		throw runtime_error("ViGEm driver hadnt connected");
	}

	hPad = vigem_target_x360_alloc();

	addBusf = vigem_target_add(dClient, hPad);
	if (!VIGEM_SUCCESS(addBusf)) {
		vigem_disconnect(dClient);
		vigem_free(dClient);
		throw runtime_error("Pad was not connected");
	}

	XInputGetState(0, &xState);
	xState.Gamepad.wButtons = 0x0000;
	vigem_target_x360_update(dClient, hPad, *reinterpret_cast<XUSB_REPORT*>(&xState.Gamepad));
}

vigemDriver::~vigemDriver()
{
	if (dClient)
	{
		vigem_target_remove(dClient, hPad);
		vigem_disconnect(dClient);
		vigem_free(dClient);
	}
}

/*
void _Pipe::Init()
{
	NamedPipe = CreateNamedPipe(
		PIPE_CHANNEL_NAME,
		PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		1,
		PIPE_SIZE,
		PIPE_SIZE,
		0,
		nullptr
	);

	if (NamedPipe == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		throw std::runtime_error("Pipe create err: " + std::to_string(err));
	}

	BOOL ConnectPipe = ConnectNamedPipe(NamedPipe, NULL);

	if (!ConnectPipe)
	{
		DWORD err = GetLastError();
		if (err != ERROR_PIPE_CONNECTED)
		{
			CloseHandle(NamedPipe);
			throw std::runtime_error("wait msg error");
		}
	}
}

_Pipe::~_Pipe()
{
	CloseHandle(NamedPipe);
}
*/