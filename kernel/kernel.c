#include <stdint.h>
#include "../../include/kernel/tty.h"

#include "../../include/kernel/tty.h"
// Forward declaration of the assembly function
extern void enter_protected_mode(void);
extern void enter_long_mode(void);

void kmain(void) {
    // Call the function to enter protected mode
    enter_protected_mode();

    // Continue with higher-level initialization in protected mode
    // For example, setting up more complex structures or data

    // Call the function to enter long mode
    enter_long_mode();

    // Main loop or further kernel initialization in long mode
    while (1) {
        // Main loop of the kernel
    }
}

void pm_main(void) {
    // This function runs in protected mode
    initializeTerminal();
    setupMemory();
    while (1) {
        // Main loop of the kernel
    }
}

void lm_main(void) {
    // This function runs in long mode
    while (1) {
        // Main loop of the kernel in long mode
    }
}
