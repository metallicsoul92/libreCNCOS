#ifndef LCNC_KERNEL_ISR_H
#define LCNC_KERNEL_ISR_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

#define ISR_COUNT 256

typedef struct {
    uint64_t ds;
    uint64_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, eflags, userrsp, ss;
} isr_regs_t;

typedef void (*isr_t)(isr_regs_t*);

void isr_install(void);
void isr_register_handler(uint8_t n, isr_t handler);

#endif // LCNC_KERNEL_ISR_H
