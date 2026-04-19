/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#pragma once

#include "ViGEm/Client.h"

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