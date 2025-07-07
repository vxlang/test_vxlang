#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#pragma optimize("", off)

//

#pragma pack(push, 1)
using register_t = size_t;
typedef struct _tag_sdk_context {
    register_t rax;
    register_t rbx;
    register_t rcx;
    register_t rdx;

    register_t rsi;
    register_t rdi;

    register_t rsp;
    register_t rbp;

    register_t r8;
    register_t r9;
    register_t r10;
    register_t r11;
    register_t r12;
    register_t r13;
    register_t r14;
    register_t r15;

    register_t efl;

    register_t src;
} context_t;
#pragma pack(pop)

//

extern "C"
void TestCallback(uint32_t id, context_t * ctx) {
    register_t ret = *(register_t*)(ctx->rsp);
    printf("src:%I64x, rsp:%I64x, ret:%I64x \n", ctx->src, ctx->rsp, ret);

    return;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE;
}


