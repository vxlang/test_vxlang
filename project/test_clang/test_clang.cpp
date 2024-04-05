#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define USE_VL_MACRO
#include "vxlib.h"

#pragma optimize("", off)

void hello() {
    VL_CODE_FLATTENING_BEGIN;

    for (int i = 0; i < 10; ++i) {
        printf("Hello, World! \n");
        Sleep(100);
    }

    VL_CODE_FLATTENING_END;

    return;
}

int main() {
    VL_CODE_FLATTENING_BEGIN;

    hello();

    VL_CODE_FLATTENING_END;

    return 1;
}


