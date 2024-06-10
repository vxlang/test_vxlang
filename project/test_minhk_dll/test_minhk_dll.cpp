#include <windows.h>
#include <stdio.h>
#include <stdint.h>

// MIN-HOOK LIB

#include "../../externals/minhook/include/MinHook.h"

// VXLANG LIB

#define USE_VL_MACRO
#include "vxlib.h"

#if defined _M_X64
#pragma comment(lib, "../../externals/minhook/lib/minhook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "../../externals/minhook/lib/minhook.x32.lib")
#endif

//

typedef int (WINAPI* MESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);

// Pointer for calling original MessageBoxW.
MESSAGEBOXW fpMessageBoxW = NULL;

// Detour function which overrides MessageBoxW.
int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
    //VL_VIRTUALIZATION_BEGIN;

    int result = fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);

    //VL_VIRTUALIZATION_END;

    return result;
}

void Hook() {
    do {
        // Initialize MinHook.
        if (MH_Initialize() != MH_OK) { break; }

        // Create a hook for MessageBoxW, in disabled state.
        if (MH_CreateHook(&MessageBoxW, &DetourMessageBoxW, reinterpret_cast<LPVOID*>(&fpMessageBoxW)) != MH_OK) { break; }

        // Enable the hook for MessageBoxW.
        if (MH_EnableHook(&MessageBoxW) != MH_OK) { break; }

    } while (false);

    return;
}

void Unhook() {
    do {
        // Disable the hook for MessageBoxW.
        if (MH_DisableHook(&MessageBoxW) != MH_OK) { break; }

    } while (false);

    return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (DLL_PROCESS_ATTACH == fdwReason) {
        printf("DLL_PROCESS_ATTACH:: \n");
        //Hook();
    }
    else if (DLL_PROCESS_DETACH == fdwReason) {
        printf("DLL_PROCESS_DETACH:: \n");
        Unhook();
    }

    return TRUE;
}

//



//

// Explained in p. 2 below
void NTAPI TlsCallback1(PVOID DllHandle, DWORD dwReason, PVOID)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        __try {
            DebugBreak();
        }
        __except(1) {
            MessageBox(nullptr, L"", L"", MB_OK);
        }

        Hook();
        //MessageBox(0, L"DLL_PROCESS_ATTACH", L"1", 0);
    }
}

#ifdef _WIN64
#pragma comment (linker, "/INCLUDE:_tls_used")  // See p. 1 below
#pragma comment (linker, "/INCLUDE:tls_callback_func")  // See p. 3 below
#else
#pragma comment (linker, "/INCLUDE:__tls_used")  // See p. 1 below
#pragma comment (linker, "/INCLUDE:_tls_callback_func")  // See p. 3 below
#endif

// Explained in p. 3 below
#ifdef _WIN64
#pragma const_seg(".CRT$XLC")
EXTERN_C const
#else
#pragma data_seg(".CRT$XLC")
EXTERN_C
#endif
PIMAGE_TLS_CALLBACK tls_callback_func[] = { TlsCallback1, };
#ifdef _WIN64
#pragma const_seg()
#else
#pragma data_seg()
#endif //_WIN64
