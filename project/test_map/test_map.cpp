#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define USE_VL_MACRO
#include "vxlib.h"

#pragma optimize("", off)

void hello() {
    for (int i = 0; i < 10; ++i) {
        printf("Hello, World! \n");
        Sleep(100);
    }

    return;
}

int main() {
    hello();

    return 1;
}


