/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "main.h"
#include <cstdio>

using namespace std;

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
int main(int agrc, char* argv[])
{
	try
	{
		vigemDriver vd;
	}
	catch (runtime_error& err)
	{
		cout << err.what();
		return 1;
	}

	return 0;
}

vigemDriver::vigemDriver()
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
