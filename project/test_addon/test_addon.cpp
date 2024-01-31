#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#pragma comment(linker, "/ALIGN:0x10000")
#pragma optimize("", off)

//

enum VXLANG_EVENT_ID {
    EVENT_LOAD_ADDON = 0xA0000000,

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

//

void Drop(const char* fileName, void* ptr, size_t size) {
    do {
        FILE* fp = fopen(fileName, "w+b");
        if (nullptr == fp) {
            break;
        }

        fwrite(ptr, size, 1, fp);
        fclose(fp);
    } while (false);

    return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (EVENT_LOAD_ADDON == fdwReason) {
        do {
            VXLANG_INTERFACE* table = (VXLANG_INTERFACE*)lpvReserved;
            if (nullptr == table) {
                break;
            }

            // *** 

            if (TRUE == IsDebuggerPresent()) { 
                table->_term("debug-detected !");
            }

            // *** 

            uint32_t size = 0;
            void* ptr = table->_raw("test", &size);
            if (nullptr == ptr || 0 == size) {
                break;
            }

            Drop("test_drop.dll", ptr, size);
            table->_free(ptr);

            LoadLibraryA("test_drop.dll");

        } while (false);
    }

    return TRUE;
}

