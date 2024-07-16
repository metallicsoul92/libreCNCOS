// pml4.c

#include "../include/kernel/pml4.h"
#include <stddef.h>

// Zero out the entire table
static void clear_table(page_entry_t *table) {
    for (size_t i = 0; i < PML4_SIZE; i++) {
        table[i] = 0;
    }
}

void setup_pml4(page_entry_t *pml4) {
    clear_table(pml4);
}

void map_page(page_entry_t *pml4, uint64_t virt_addr, uint64_t phys_addr, uint64_t flags) {
    // Get the PML4 entry
    page_entry_t *pdpt;
    if (!(pml4[PML4_ENTRY(virt_addr)] & PAGE_PRESENT)) {
        pdpt = (page_entry_t *) ((uint64_t)malloc(4096) & ~0xFFF);
        clear_table(pdpt);
        pml4[PML4_ENTRY(virt_addr)] = (uint64_t)pdpt | flags | PAGE_PRESENT;
    } else {
        pdpt = (page_entry_t *)(pml4[PML4_ENTRY(virt_addr)] & ~0xFFF);
    }

    // Get the PDPT entry
    page_entry_t *pd;
    if (!(pdpt[PDPT_ENTRY(virt_addr)] & PAGE_PRESENT)) {
        pd = (page_entry_t *) ((uint64_t)malloc(4096) & ~0xFFF);
        clear_table(pd);
        pdpt[PDPT_ENTRY(virt_addr)] = (uint64_t)pd | flags | PAGE_PRESENT;
    } else {
        pd = (page_entry_t *)(pdpt[PDPT_ENTRY(virt_addr)] & ~0xFFF);
    }

    // Get the PD entry
    page_entry_t *pt;
    if (!(pd[PD_ENTRY(virt_addr)] & PAGE_PRESENT)) {
        pt = (page_entry_t *) ((uint64_t)malloc(4096) & ~0xFFF);
        clear_table(pt);
        pd[PD_ENTRY(virt_addr)] = (uint64_t)pt | flags | PAGE_PRESENT;
    } else {
        pt = (page_entry_t *)(pd[PD_ENTRY(virt_addr)] & ~0xFFF);
    }

    // Map the page
    pt[PT_ENTRY(virt_addr)] = phys_addr | flags | PAGE_PRESENT;
}
