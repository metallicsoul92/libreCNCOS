#include "../include/kernel/isr.h"
#include "../include/kernel/idt.h"
#include "../libc/crt/include/stdio.h"
#include "../libc/crt/include/string.h"

// Array to store ISR handler functions
isr_t isr_handlers[ISR_COUNT] = { 0 };

// Function to register an ISR handler
void isr_register_handler(uint8_t n, isr_t handler) {
    if (n < ISR_COUNT) {
        isr_handlers[n] = handler;
    }
}

// The common ISR handler called from the assembly stubs
void isr_handler(isr_regs_t *regs) {
    if (regs->int_no < ISR_COUNT && isr_handlers[regs->int_no]) {
        isr_t handler = isr_handlers[regs->int_no];
        handler(regs);
    } else {
        // Optionally: add code to halt the system or perform other error handling
    }
}

// Individual ISR handler functions
#define DEFINE_ISR_HANDLER(n)                  \
void isr##n##_handler() {                      \
    asm volatile (                             \
        "cli\n\t"                              \
        "push %rax\n\t"                       \
        "push %rbx\n\t"                       \
        "push %rcx\n\t"                       \
        "push %rdx\n\t"                       \
        "push %rsi\n\t"                       \
        "push %rdi\n\t"                       \
        "push %rbp\n\t"                       \
        "push %r8\n\t"                        \
        "push %r9\n\t"                        \
        "push %r10\n\t"                       \
        "push %r11\n\t"                       \
        "push %r12\n\t"                       \
        "push %r13\n\t"                       \
        "push %r14\n\t"                       \
        "push %r15\n\t"                       \
        "mov %rsp, %rdi\n\t"                 \
        "call isr_handler\n\t"                 \
        "pop %r15\n\t"                        \
        "pop %r14\n\t"                        \
        "pop %r13\n\t"                        \
        "pop %r12\n\t"                        \
        "pop %r11\n\t"                        \
        "pop %r10\n\t"                        \
        "pop %r9\n\t"                         \
        "pop %r8\n\t"                         \
        "pop %rbp\n\t"                        \
        "pop %rdi\n\t"                        \
        "pop %rsi\n\t"                        \
        "pop %rdx\n\t"                        \
        "pop %rcx\n\t"                        \
        "pop %rbx\n\t"                        \
        "pop %rax\n\t"                        \
        "sti\n\t"                              \
        "iretq\n\t"                            \
    );                                         \
}

// Define ISR handlers for 0 to 31
DEFINE_ISR_HANDLER(0)
DEFINE_ISR_HANDLER(1)
DEFINE_ISR_HANDLER(2)
DEFINE_ISR_HANDLER(3)
DEFINE_ISR_HANDLER(4)
DEFINE_ISR_HANDLER(5)
DEFINE_ISR_HANDLER(6)
DEFINE_ISR_HANDLER(7)
DEFINE_ISR_HANDLER(8)
DEFINE_ISR_HANDLER(9)
DEFINE_ISR_HANDLER(10)
DEFINE_ISR_HANDLER(11)
DEFINE_ISR_HANDLER(12)
DEFINE_ISR_HANDLER(13)
DEFINE_ISR_HANDLER(14)
DEFINE_ISR_HANDLER(15)
DEFINE_ISR_HANDLER(16)
DEFINE_ISR_HANDLER(17)
DEFINE_ISR_HANDLER(18)
DEFINE_ISR_HANDLER(19)
DEFINE_ISR_HANDLER(20)
DEFINE_ISR_HANDLER(21)
DEFINE_ISR_HANDLER(22)
DEFINE_ISR_HANDLER(23)
DEFINE_ISR_HANDLER(24)
DEFINE_ISR_HANDLER(25)
DEFINE_ISR_HANDLER(26)
DEFINE_ISR_HANDLER(27)
DEFINE_ISR_HANDLER(28)
DEFINE_ISR_HANDLER(29)
DEFINE_ISR_HANDLER(30)
DEFINE_ISR_HANDLER(31)

// Initialization function to set up ISRs
void isr_install() {
    // Register example ISR handlers for testing
    for (uint8_t i = 0; i < 32; i++) {
        isr_register_handler(i, isr_example_handler);
    }
    // You can register more handlers here as needed
}
