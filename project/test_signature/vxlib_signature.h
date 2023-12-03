#pragma once

#include <intrin.h>

#define VM_BEGIN            __nop(); __nop(); _enable(); __nop(); __halt();
#define VM_END              __nop(); __nop(); _disable(); __nop(); __halt();

#define OBFUSCATE_BEGIN            __nop(); _enable(); _enable(); __nop(); __halt();
#define OBFUSCATE_END              __nop(); _disable(); _disable(); __nop(); __halt();

#define CODE_FLA_BEGIN            _enable(); _enable(); _enable(); __nop(); __halt();
#define CODE_FLA_END              _disable(); _disable(); _disable(); __nop(); __halt();
