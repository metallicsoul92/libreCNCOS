#ifndef ISR_H
#define ISR_H

#ifndef __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#define __HAS_STDINT
#endif



// Number of ISRs
#define ISR_COUNT 256

// Registers structure passed to ISR handlers
typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rsi, rdi, rbp, rdx, rcx, rbx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, rflags, rsp, ss;
} isr_regs_t;

// Define the type for ISR handler functions
typedef void (*isr_t)(isr_regs_t *);

// Function to register an ISR handler
void isr_register_handler(uint8_t n, isr_t handler);

// Common ISR handler
void isr_handler(isr_regs_t *regs);

// Example ISR handler
void isr_example_handler(isr_regs_t *regs);

// ISR initialization
void isr_install();

#endif // ISR_H
