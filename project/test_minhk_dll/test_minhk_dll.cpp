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
    VL_VIRTUALIZATION_BEGIN;

    int result = fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);

    VL_VIRTUALIZATION_END;

    return result;
}

void Hook() {
    VL_VIRTUALIZATION_BEGIN;

    do {
        // Initialize MinHook.
        if (MH_Initialize() != MH_OK) { break; }

        // Create a hook for MessageBoxW, in disabled state.
        if (MH_CreateHook(&MessageBoxW, &DetourMessageBoxW, reinterpret_cast<LPVOID*>(&fpMessageBoxW)) != MH_OK) { break; }

        // Enable the hook for MessageBoxW.
        if (MH_EnableHook(&MessageBoxW) != MH_OK) { break; }

    } while (false);

    VL_VIRTUALIZATION_END;

    return;
}

void Unhook() {
    VL_VIRTUALIZATION_BEGIN;

    do {
        // Disable the hook for MessageBoxW.
        if (MH_DisableHook(&MessageBoxW) != MH_OK) { break; }

    } while (false);

    VL_VIRTUALIZATION_END;

    return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    VL_VIRTUALIZATION_BEGIN;

    if (DLL_PROCESS_ATTACH == fdwReason) {
        printf("DLL_PROCESS_ATTACH:: \n");
        Hook();
    }
    else if (DLL_PROCESS_DETACH == fdwReason) {
        printf("DLL_PROCESS_DETACH:: \n");
        Unhook();
    }

    VL_VIRTUALIZATION_END;

    return TRUE;
}
