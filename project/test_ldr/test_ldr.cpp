#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#include "../../externals/lazy_importer/lazy_importer.hpp"
#include "../../externals/xorstr/xorstr.hpp"

#ifdef _WIN64
#define TEST_DLL_NAME L"test_ldr_dll64.dll"
#else
#define TEST_DLL_NAME L"test_ldr_dll32.dll"
#endif

#define USE_VL_MACRO
#include "vxlib.h"

#pragma optimize("", off)

void test_lazy_importer() {
    VL_VIRTUALIZATION_BEGIN;

    void* user32 = LI_FN(LoadLibraryA)(xorstr_("user32.dll"));
    //void* kernel32 = LI_MODULE("kernel32.dll").cached(); // *** 

    printf(xorstr_(" user32 => %p \n"), user32);
    LI_FN(MessageBoxA).in(user32)(NULL, xorstr_("hello world"), xorstr_("virtualizer"), 0);

    VL_VIRTUALIZATION_END;

    //

    VL_CODE_FLATTENING_BEGIN;

    LI_FN(MessageBoxA).in(user32)(NULL, xorstr_("hello world"), xorstr_("obfuscator"), 0);

    VL_CODE_FLATTENING_END;

    return;
}

void test_default_api() {
    VL_VIRTUALIZATION_BEGIN;

    HMODULE dll = LoadLibraryW(TEST_DLL_NAME);
    if (nullptr != dll) {
        MessageBoxW(nullptr, L"LOAD !", L"", MB_OK);
    }
    else {
        MessageBoxW(nullptr, L"ERR !", L"", MB_OK);
    }

    VL_VIRTUALIZATION_END;

    return;
}

int main() {
    VL_VIRTUALIZATION_BEGIN;

    test_lazy_importer();
    test_default_api();

    VL_VIRTUALIZATION_END;

    return 1;
}
