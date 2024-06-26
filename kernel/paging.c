#include "../include/kernel/paging.h"
#include "../include/kernel/kmalloc.h" // for kmalloc
#include "../include/kernel/pmm.h" // for alloc_page, free_page

static PageMapLevel4* pml4;

void setup_paging() {
    // Allocate memory for PML4
    pml4 = (PageMapLevel4*)alloc_page(); // Use PMM to allocate a page
    if (pml4 == NULL) {
        // Handle allocation failure
        // Example: panic or return error
        return;
    }
    // Clear PML4
    memset(pml4, 0, sizeof(PageMapLevel4));
}

int map_page(void* virtual_address, void* physical_address) {
    uint64_t virtual_addr = (uint64_t)virtual_address;
    uint64_t physical_addr = (uint64_t)physical_address;

    uint64_t pml4_index = (virtual_addr >> 39) & 0x1FF;
    uint64_t pdpt_index = (virtual_addr >> 30) & 0x1FF;
    uint64_t pd_index = (virtual_addr >> 21) & 0x1FF;
    uint64_t pt_index = (virtual_addr >> 12) & 0x1FF;

    // Ensure PDPT exists in PML4
    if (!(pml4->entries[pml4_index] & 0x1)) {
        PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)alloc_page();
        if (pdpt == NULL) {
            // Handle allocation failure
            return -1;
        }
        memset(pdpt, 0, sizeof(PageDirectoryPointerTable));
        pml4->entries[pml4_index] = (uint64_t)pdpt | 0x3; // Present, RW, User
    }

    PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)(pml4->entries[pml4_index] & ~0xFFF);

    // Ensure PD exists in PDPT
    if (!(pdpt->entries[pdpt_index] & 0x1)) {
        PageDirectory* pd = (PageDirectory*)alloc_page();
        if (pd == NULL) {
            // Handle allocation failure
            return -1;
        }
        memset(pd, 0, sizeof(PageDirectory));
        pdpt->entries[pdpt_index] = (uint64_t)pd | 0x3; // Present, RW, User
    }

    PageDirectory* pd = (PageDirectory*)(pdpt->entries[pdpt_index] & ~0xFFF);

    // Ensure PT exists in PD
    if (!(pd->entries[pd_index] & 0x1)) {
        PageTable* pt = (PageTable*)alloc_page();
        if (pt == NULL) {
            // Handle allocation failure
            return -1;
        }
        memset(pt, 0, sizeof(PageTable));
        pd->entries[pd_index] = (uint64_t)pt | 0x3; // Present, RW, User
    }

    PageTable* pt = (PageTable*)(pd->entries[pd_index] & ~0xFFF);

    // Map physical address to PT entry
    pt->entries[pt_index] = (physical_addr & ~0xFFF) | 0x3; // Present, RW, User
    return 0;
}

void* translate(void* virtual_address) {
    uint64_t virtual_addr = (uint64_t)virtual_address;

    uint64_t pml4_index = (virtual_addr >> 39) & 0x1FF;
    uint64_t pdpt_index = (virtual_addr >> 30) & 0x1FF;
    uint64_t pd_index = (virtual_addr >> 21) & 0x1FF;
    uint64_t pt_index = (virtual_addr >> 12) & 0x1FF;

    if (!(pml4->entries[pml4_index] & 0x1))
        return NULL; // Not mapped

    PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)(pml4->entries[pml4_index] & ~0xFFF);

    if (!(pdpt->entries[pdpt_index] & 0x1))
        return NULL; // Not mapped

    PageDirectory* pd = (PageDirectory*)(pdpt->entries[pdpt_index] & ~0xFFF);

    if (!(pd->entries[pd_index] & 0x1))
        return NULL; // Not mapped

    PageTable* pt = (PageTable*)(pd->entries[pd_index] & ~0xFFF);

    if (!(pt->entries[pt_index] & 0x1))
        return NULL; // Not mapped

    uint64_t physical_addr = (pt->entries[pt_index] & ~0xFFF);
    physical_addr |= (virtual_addr & 0xFFF);

    return (void*)physical_addr;
}

void unmap_page(void* virtual_address) {
    uint64_t virtual_addr = (uint64_t)virtual_address;

    uint64_t pml4_index = (virtual_addr >> 39) & 0x1FF;
    uint64_t pdpt_index = (virtual_addr >> 30) & 0x1FF;
    uint64_t pd_index = (virtual_addr >> 21) & 0x1FF;
    uint64_t pt_index = (virtual_addr >> 12) & 0x1FF;

    if (!(pml4->entries[pml4_index] & 0x1))
        return; // Not mapped

    PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)(pml4->entries[pml4_index] & ~0xFFF);

    if (!(pdpt->entries[pdpt_index] & 0x1))
        return; // Not mapped

    PageDirectory* pd = (PageDirectory*)(pdpt->entries[pdpt_index] & ~0xFFF);

    if (!(pd->entries[pd_index] & 0x1))
        return; // Not mapped

    PageTable* pt = (PageTable*)(pd->entries[pd_index] & ~0xFFF);

    if (!(pt->entries[pt_index] & 0x1))
        return; // Not mapped

    pt->entries[pt_index] = 0;

    // Optionally, free the page table if no more entries are used
    // This requires additional bookkeeping to track page table usage
    // and deallocate when no longer needed.
}
