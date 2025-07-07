#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#include <vector>
#include <mutex>

#include "../../externals/lazy_importer/lazy_importer.hpp"
#include "../../externals/xorstr/xorstr.hpp"

#ifdef _WIN64
#pragma comment(lib, "test_callback_dll64.lib")
#else
#pragma comment(lib, "test_callback_dll32.lib")
#endif

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

extern "C"
void TestCallback(uint32_t id, context_t * ctx);

//

extern "C"
void VxLangEventCallback(uint32_t id, context_t * ctx) {
    TestCallback(id, ctx);

    return;
}

int main() {
    MessageBox(nullptr, L"Start", L"", MB_OK);

    printf("run .. \n");

    MessageBox(nullptr, L"End", L"", MB_OK);

    return 1;
}
