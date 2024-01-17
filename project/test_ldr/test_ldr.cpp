#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#ifdef _WIN64
#define TEST_DLL_NAME L"test_ldr_dll64.dll"
#else
#define TEST_DLL_NAME L"test_ldr_dll32.dll"
#endif

#define USE_VL_MACRO
#include "vxlib.h"

#pragma optimize("", off)

int main() {
    VL_VIRTUALIZATION_BEGIN;

    HMODULE dll = LoadLibraryW(TEST_DLL_NAME);
    if (nullptr != dll) {
        MessageBoxW(nullptr, L"LOAD !", L"", MB_OK);
    }
    else {
        MessageBoxW(nullptr, L"ERR !", L"", MB_OK);
    }

    VL_VIRTUALIZATION_END;

    return 1;
}
