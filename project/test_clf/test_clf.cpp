#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define USE_VL_MACRO
#include "vxlib.h"

#pragma optimize("", off)

//

void lv1() {
    VL_CODE_FLATTENING_LV_BEGIN(1);

    printf("LV 1 \n");

    VL_CODE_FLATTENING_LV_END(1);

    return;
}

int main() {
    VL_CODE_FLATTENING_BEGIN;

    int i = 0;
    while (true) {
        lv1();
        Sleep(1000);
    }

    VL_CODE_FLATTENING_END;

    return 1;
}


