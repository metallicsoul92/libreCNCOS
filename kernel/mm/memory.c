#include "../../include/kernel/mm/memory.h"



uint8_t setupMemory() {
    /* Calculate total memory */
    size_t total_memory = 1024 * 1024 * 10; // 10MB to start with

    // Initialize physical memory manager (pmm)
    init_pmm(total_memory);

    // Initialize virtual memory manager (vmm)
    init_vmm();

    // Setup paging structures
    setup_paging();

    return 0; // Return success
}
