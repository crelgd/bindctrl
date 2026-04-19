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

private:
	PVIGEM_CLIENT dClient;
	VIGEM_ERROR dConnection;
};