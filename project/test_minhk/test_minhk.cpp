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
    VL_VIRTUALIZATION_BEGIN;

    int result = fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);

    VL_VIRTUALIZATION_END;

    return result;
}

int main() {
    
#ifdef _WIN64
    const wchar_t dllName[] = L"test_minhk_dll64.dll";
#else
    const wchar_t dllName[] = L"test_minhk_dll32.dll";
#endif
    auto minhkDll = LoadLibraryW(dllName);

    MessageBoxW(nullptr, L"Test ..", L"", MB_OK);

    FreeLibrary(minhkDll);

    MessageBoxW(nullptr, L"Test ..", L"", MB_OK);

    return 0;
}


