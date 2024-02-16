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

void seh() {
    VL_CODE_FLATTENING_BEGIN;

    __try {
        //printf("CodeFlattening \n");
        __debugbreak();
    }
    __except (1) {
        printf("__except ! \n");
    }

    VL_CODE_FLATTENING_END;


    //

    __try {
        __debugbreak();
        __debugbreak();
    }
    __except (1) {
        printf("ObfuscateSEH_1:: SEH 2 \n");
    }

    //

    VL_CODE_FLATTENING_BEGIN;

    __try {
        __debugbreak();
    }
    __except (1) {
        printf("ObfuscateSEH_1:: SEH 3 \n");
    }

    VL_CODE_FLATTENING_END;

    return;
}

int main() {
    VL_CODE_FLATTENING_BEGIN;

    seh();

    VL_CODE_FLATTENING_END;

    //

    VL_CODE_FLATTENING_BEGIN;

    for (int i = 0; i < 10; ++i) {
        printf("%d \n", i);
        Sleep(100);
    }

    VL_CODE_FLATTENING_END;

    //

    int i = 10;

    VL_CODE_FLATTENING_BEGIN;

    if (10 == i) {
        printf(" :] ! \n");
    }
    else {
        printf(" :[ ! \n");
    }

    VL_CODE_FLATTENING_END;

    return 1;
}


