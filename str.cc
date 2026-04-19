/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "main.h"

void FilePathNearbyMain(
	char* dst,
	size_t dstSizeInByte,
	const char* fileName,
	size_t fnSizeInByte
)
{
	size_t pathSize;

	GetModuleFileNameA(NULL, dst, dstSizeInByte);
	pathSize = strlen(dst);

	for (int i = pathSize; i > 0; i--) {
		if (dst[i] == '\\') {
			pathSize = i + 1;
			break;
		}
	}

	memcpy(dst + pathSize, fileName, fnSizeInByte);

	char toAdd[2] = "\0";
	for (int i = 0; i < 1; i++) {
		dst[pathSize + fnSizeInByte + i] = toAdd[i];
	}
}

int ConvertWSTR(char* in, wchar_t* out, int wcharLen)
{
	size_t retVal;		// переменная с колическом переведенных символов

	errno_t err = mbstowcs_s(&retVal,
		out,
		wcharLen,
		in,
		DIRECTION_SIZE);

	if (err != 0)
		return 1;

	return 0;
}