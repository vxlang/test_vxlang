#include <windows.h>
#include <stdio.h>

#include "vxlib.h"

#pragma optimize("", off)

void RunProcessAttach() {
    VL_CODE_FLATTENING_BEGIN;

    MessageBox(nullptr, L"C", L"", MB_OK);

    VL_CODE_FLATTENING_END;

    //

    VL_VIRTUALIZATION_BEGIN;

    MessageBox(nullptr, L"V", L"", MB_OK);

    VL_VIRTUALIZATION_END;

    return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

    VL_VIRTUALIZATION_BEGIN;

    if (DLL_PROCESS_ATTACH == fdwReason) {
        RunProcessAttach();
    }

    VL_VIRTUALIZATION_END;

    return TRUE;
}
