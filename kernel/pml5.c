// pml5.c

#include "../include/kernel/pml5.h"
#include "../include/kernel/cpuid.h"
#include "../libc/crt/include/stddef.h"

// Check if the CPU supports PML5
int is_pml5_supported() {
    unsigned int eax, ebx, ecx, edx;
    __cpuid_count(7, 0, eax, ebx, ecx, edx);
    return ecx & (1 << 16); // Check if bit 16 in ecx is set
}

// Zero out the entire table
static void clear_table(page_entry_t *table) {
    for (size_t i = 0; i < PML5_SIZE; i++) {
        table[i] = 0;
    }
}

void setup_pml5(page_entry_t *pml5) {
    clear_table(pml5);
}

void map_page_pml5(page_entry_t *pml5, uint64_t virt_addr, uint64_t phys_addr, uint64_t flags) {
    // Get the PML5 entry
    page_entry_t *pml4;
    if (!(pml5[PML5_ENTRY(virt_addr)] & PAGE_PRESENT)) {
        pml4 = (page_entry_t *) ((uint64_t)malloc(4096) & ~0xFFF);
        clear_table(pml4);
        pml5[PML5_ENTRY(virt_addr)] = (uint64_t)pml4 | flags | PAGE_PRESENT;
    } else {
        pml4 = (page_entry_t *)(pml5[PML5_ENTRY(virt_addr)] & ~0xFFF);
    }

    // Map the rest of the pages
    map_page(pml4, virt_addr, phys_addr, flags);
}
