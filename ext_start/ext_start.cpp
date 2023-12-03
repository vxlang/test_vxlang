// vxlang.exe test_minhk.exe --add-on ext_start.dll

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#pragma comment(linker, "/ALIGN:0x10000")

enum _tag_PACKER_STATUS {
    VXLANG_INITIALIZE = 0,
    VXLANG_LOAD_ADDON_EVENT = 0xA0000000,

    VXLANG_SETUP_IMPORT_TABLE,

    VXLANG_START_EVENT,
    VXLANG_TERMINATE_EVENT,
    VXLANG_DOTNET_EVENT,

    VXLANG_ERROR_IMPORT_TABLE = 0xE0000000,
    VXLANG_ERROR_ALLOCATE_VIRTUAL_IMAGE,
    VXLANG_ERROR_RELOCATE_IMAGE,
    VXLANG_ERROR_INSTALL_FAIL,

    VXLANG_DETECTED_DEBUG = 0xD0000000,
    VXLANG_DETECTED_PATCH,
};

//

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    BOOL result = TRUE;

    switch (fdwReason) {
    case VXLANG_LOAD_ADDON_EVENT:
        MessageBoxW(nullptr, L"Load Exts", L"", MB_OK);
        break;
    case VXLANG_START_EVENT:
        MessageBoxW(nullptr, L"Start Process", L"", MB_OK);
        break;
    default:
        break;
    }

    return result;
}

