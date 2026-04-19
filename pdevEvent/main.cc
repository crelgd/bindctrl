/*
 * MIT License
 * Copyright (c) 2026 crelgd
 */

#include "pdevevent.h"
#include "main.h"

HANDLE pipe;

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    HANDLE thInit;

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        {
            thInit = CreateThread(NULL, 0, [](LPVOID) -> DWORD{
               while (true) {
                    HANDLE npipe = CreateFileW(
                        PIPE_CHANNEL_NAME,
                        GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                    );
                    if (npipe != INVALID_HANDLE_VALUE) {
                        pipe = npipe;
                        break;
                    }

                    Sleep(50);
                }

                return 0;
            }, nullptr, 0, NULL);
            if (thInit) CloseHandle(thInit);
        }
        break;

    case DLL_PROCESS_DETACH:
        {
            if (pipe && pipe != INVALID_HANDLE_VALUE)
                CloseHandle(pipe);
        }
        break;
    }

    return TRUE;
}
