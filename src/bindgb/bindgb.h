/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#pragma once

#define RUNTIME_DIR	L"runtime"
#define PY_DLL		L"python313.dll"

class Python
{
public:
	Python();
	~Python();

	int Init();
	int Direction();

private:
	typedef int (*_PyMain)(int argc, wchar_t** argv);
	HINSTANCE hDLL;

	std::wstring runtimePath;
	std::wstring home;
	std::wstring dllPath;

public:
	_PyMain Py_Main;
};
