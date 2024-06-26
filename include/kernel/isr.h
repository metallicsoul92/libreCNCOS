#ifndef LCNC_KERNEL_ISR_H
#define LCNC_KERNEL_ISR_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include <stdint.h>
#endif


// Define the structure for the CPU registers when an ISR occurs
typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, eflags, rsp, ss;
} isr_regs_t;

// Function pointer type for ISR handlers
typedef void (*isr_t)(isr_regs_t *);

// Array of ISR handlers
#define ISR_COUNT 256
extern isr_t isr_handlers[ISR_COUNT];

// ISR handler registration function
void isr_register_handler(uint8_t n, isr_t handler);

// Common ISR handler called from the assembly stubs
void isr_handler(isr_regs_t *regs);

#endif // ISR_H
