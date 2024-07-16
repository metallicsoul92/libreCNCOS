#ifndef LCNC_KERNEL_REGISTERS_H
#define LCNC_KERNEL_REGISTERS_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

// Register state for x86-64
typedef struct {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rsp;
    uint64_t rbp;
    uint64_t rip;
    uint64_t rflags;
    uint64_t cr3; // Page directory base register for virtual memory
} reg_t;

#endif // LCNC_KERNEL_REGISTERS_H
