/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "bindgb.h"

#include <iostream>
#include <fstream>
#include <filesystem>

Python::Python()
{
	hDLL = NULL;
	Py_Main = NULL;

	if (Direction())
		exit(1);
	if (Init())
	{
		exit(2);
	}
}

Python::~Python()
{
	if (hDLL) FreeLibrary(hDLL);
}

int Python::Direction()
{
	wchar_t exePath[2048] = { 0 };
	GetModuleFileNameW(NULL, exePath, 2048);

	home = std::filesystem::path(exePath).parent_path();
	home += L"\\";

	runtimePath = home + RUNTIME_DIR + L"\\";
	
	dllPath = runtimePath + PY_DLL;

	return 0;
}

int Python::Init()
{
	SetCurrentDirectoryW(runtimePath.c_str());
	//SetDllDirectory(runtimePath.c_str());

	//WCHAR env[65535];
	//GetEnvironmentVariableW(L"PATH", env, 65535);
	//auto newenv = std::wstring(env) + L";" + runtimePath;

	//SetEnvironmentVariableW(L"PATH", newenv.c_str());

	hDLL = (HINSTANCE)LoadLibraryW(dllPath.c_str());
	
	if (hDLL) {
		Py_Main = (_PyMain)GetProcAddress(hDLL, "Py_Main");
	}

	SetCurrentDirectory(home.c_str());

	if (!hDLL) {
		MessageBoxA(NULL, "dll not found", "err", 0);
		return 1;
	}

	if (!Py_Main) {
		MessageBoxA(NULL, "Py_Main not found", "err", 0);
		return 1;
	}

	return 0;
}

int main()
{
	Python py;

	if (AttachConsole(ATTACH_PARENT_PROCESS))
	{
		FILE* stream = nullptr;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONOUT$", "w", stderr);
	}

	return py.Py_Main(__argc, __wargv);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	return main();
}
