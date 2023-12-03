#include <windows.h>
#include <stdio.h>
#include <stdint.h>

// MIN-HOOK LIB

#include "../../externals/minhook/include/MinHook.h"

#if defined _M_X64
#pragma comment(lib, "../../externals/minhook/lib/minhook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "../../externals/minhook/lib/minhook.x32.lib")
#endif

// VXLANG LIB

#define USE_VL_MACRO
#include "vxlib.h"

//

typedef int (WINAPI* MESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);

// Pointer for calling original MessageBoxW.
MESSAGEBOXW fpMessageBoxW = NULL;

// Detour function which overrides MessageBoxW.
int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
    VL_CODE_FLATTENING_LV_BEGIN(3);

    int result = fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);

    VL_CODE_FLATTENING_LV_END(3);

    return result;
}

int main() {
    VL_CODE_FLATTENING_LV_BEGIN(3);

    // Initialize MinHook.
    if (MH_Initialize() != MH_OK) {
        return 1;
    }

    // Create a hook for MessageBoxW, in disabled state.
    if (MH_CreateHook(&MessageBoxW, &DetourMessageBoxW,
        reinterpret_cast<LPVOID*>(&fpMessageBoxW)) != MH_OK) {
        return 1;
    }

    // or you can use the new helper function like this.
    //if (MH_CreateHookApiEx(
    //    L"user32", "MessageBoxW", &DetourMessageBoxW, &fpMessageBoxW) != MH_OK)
    //{
    //    return 1;
    //}

    // Enable the hook for MessageBoxW.
    if (MH_EnableHook(&MessageBoxW) != MH_OK) {
        return 1;
    }

    // Expected to tell "Hooked!".
    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    // Disable the hook for MessageBoxW.
    if (MH_DisableHook(&MessageBoxW) != MH_OK) {
        return 1;
    }

    // Expected to tell "Not hooked...".
    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    // Uninitialize MinHook.
    if (MH_Uninitialize() != MH_OK) {
        return 1;
    }

    VL_CODE_FLATTENING_LV_END(3);

    return 0;
}
