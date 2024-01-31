#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#include "vxlib.h"

#pragma optimize("", off)

//

int main() {
    VL_VIRTUALIZATION_BEGIN;

    int i = 0;
    while (true) {
        printf("%d \r", ++i);
        Sleep(1000);
    }

    VL_VIRTUALIZATION_END;

    return 1;
}

//

enum VXLANG_EVENT_ID {
    EVENT_DEBUG_DETECTED = 0xD0000000,
    EVENT_PATCH_DETECTED,
    EVENT_CHKIMG_DETECTED,
};

typedef void* (__stdcall* GetRawDataT)(const char* keyName, uint32_t* size);
typedef void(__stdcall* FreeRawDataT)(void* ptr);
typedef bool(__stdcall* TerminateT)(const char* message);

typedef struct _tag_VXLANG_INTERFACE {
    GetRawDataT _raw;
    FreeRawDataT _free;
    TerminateT _term;
} VXLANG_INTERFACE;

void __stdcall TestEventHandle(uint32_t id, void* context) {
    VL_VIRTUALIZATION_BEGIN;

    VXLANG_INTERFACE* interfaceTable = (VXLANG_INTERFACE*)context;
    if (EVENT_DEBUG_DETECTED == id) {
        printf("[EVENT_DEBUG_DETECTED] \n");
        interfaceTable->_term("test-detected .. !");
    }

    VL_VIRTUALIZATION_END;

    return;
}

