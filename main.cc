/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "main.h"
#include <iostream>

using namespace std;

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
	if (!VIGEM_SUCCESS(dConnection))
		throw runtime_error("ViGEm driver hadnt connected");
}

vigemDriver::~vigemDriver()
{
	if (dClient)
	{
		vigem_disconnect(dClient);
		vigem_free(dClient);
	}
}