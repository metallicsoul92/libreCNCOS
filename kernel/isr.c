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
        //printk("Unhandled interrupt: %d\n", regs->int_no);
        // Optionally: add code to halt the system or perform other error handling
    }
}

// An example ISR handler for testing purposes
void isr_example_handler(isr_regs_t *regs) {
    //printk("Received interrupt: %d\n", regs->int_no);
    // Perform additional handling as needed
}

// Initialization function to set up ISRs
void isr_install() {
    // Register example ISR handlers for testing
    for (uint8_t i = 0; i < 32; i++) {
        isr_register_handler(i, isr_example_handler);
    }
    // You can register more handlers here as needed
}
