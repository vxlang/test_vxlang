#include <windows.h>
#include <stdio.h>

#include "vxlib.h"

#pragma optimize("", off)

void hello() {
    for (int i = 0; i < 10; ++i) {
        printf("Hello ! \n");
    }
    return;
}

void test() {
    VL_VIRTUALIZATION_BEGIN;

    // *** There may be conflicts between SDK and MAP-based obfuscation.

    for (int i = 0; i < 10; ++i) {
        printf("RUN !! \n");
    }

    VL_VIRTUALIZATION_END;

    return;
}

int main() {
    hello();
    test();

    MessageBox(nullptr, L"DONE", L"", MB_OK);

    return 1;
}


