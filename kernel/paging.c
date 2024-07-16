#include "../include/kernel/paging.h"
#include "../include/kernel/mm/memory.h"
#include "../libc/crt/include/string.h"

PageMapLevel4 *pml4;


void load_page_directory(uint32_t* page_directory) {
    // Load page directory
    asm volatile("mov %0, %%cr3" : : "r"(page_directory));
}

void enable_paging() {
    // Enable paging
    uint64_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Set the paging bit
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

static inline uint64_t* get_pml4_entry(void* virtual_address) {
    return &pml4->entries[((uint64_t)virtual_address >> 39) & 0x1FF];
}

static inline uint64_t* get_pdpt_entry(PageDirectoryPointerTable* pdpt, void* virtual_address) {
    return &pdpt->entries[((uint64_t)virtual_address >> 30) & 0x1FF];
}

static inline uint64_t* get_pd_entry(PageDirectory* pd, void* virtual_address) {
    return &pd->entries[((uint64_t)virtual_address >> 21) & 0x1FF];
}

static inline uint64_t* get_pt_entry(PageTable* pt, void* virtual_address) {
    return &pt->entries[((uint64_t)virtual_address >> 12) & 0x1FF];
}

void setup_paging(void) {
    // Allocate memory for PML4
    pml4 = (PageMapLevel4*)alloc_page(); // Use PMM to allocate a page
    if (pml4 == NULL) {
        // Handle allocation failure
        // Example: panic or return error

        return;
    }
    // Clear PML4
    memset(pml4, 0, sizeof(PageMapLevel4));

    // Allocate memory for PDPT
    PageDirectoryPointerTable *pdpt = (PageDirectoryPointerTable*)alloc_page();
    if (pdpt == NULL) {
        // Handle allocation failure
        return;
    }
    memset(pdpt, 0, sizeof(PageDirectoryPointerTable));

    // Allocate memory for PD
    PageDirectory *pd = (PageDirectory*)alloc_page();
    if (pd == NULL) {
        // Handle allocation failure
        return;
    }
    memset(pd, 0, sizeof(PageDirectory));

    // Allocate memory for PT
    PageTable *pt = (PageTable*)alloc_page();
    if (pt == NULL) {
        // Handle allocation failure
        return;
    }
    memset(pt, 0, sizeof(PageTable));

    // Identity map the first 2MB of memory
    for (int i = 0; i < 512; i++) {
        pt->entries[i] = (i * PAGE_SIZE) | 0x3; // Present, RW
    }

    // Set up the PD to point to the PT
    pd->entries[0] = ((uint64_t)pt) | 0x3; // Present, RW

    // Set up the PDPT to point to the PD
    pdpt->entries[0] = ((uint64_t)pd) | 0x3; // Present, RW

    // Set up the PML4 to point to the PDPT
    pml4->entries[0] = ((uint64_t)pdpt) | 0x3; // Present, RW

    // Load the PML4 into CR3
    load_page_directory((uint64_t*)pml4);

    // Enable paging by setting the paging bit in CR0
    enable_paging();
}

int map_page(void* virtual_address, void* physical_address) {
    uint64_t* pml4_entry = get_pml4_entry(virtual_address);
    if (!(*pml4_entry & 0x1)) {
        PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)alloc_page();
        if (pdpt == NULL) return -1;
        memset(pdpt, 0, sizeof(PageDirectoryPointerTable));
        *pml4_entry = ((uint64_t)pdpt) | 0x3; // Present, RW
    }
    PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)(*pml4_entry & ~0xFFF);

    uint64_t* pdpt_entry = get_pdpt_entry(pdpt, virtual_address);
    if (!(*pdpt_entry & 0x1)) {
        PageDirectory* pd = (PageDirectory*)alloc_page();
        if (pd == NULL) return -1;
        memset(pd, 0, sizeof(PageDirectory));
        *pdpt_entry = ((uint64_t)pd) | 0x3; // Present, RW
    }
    PageDirectory* pd = (PageDirectory*)(*pdpt_entry & ~0xFFF);

    uint64_t* pd_entry = get_pd_entry(pd, virtual_address);
    if (!(*pd_entry & 0x1)) {
        PageTable* pt = (PageTable*)alloc_page();
        if (pt == NULL) return -1;
        memset(pt, 0, sizeof(PageTable));
        *pd_entry = ((uint64_t)pt) | 0x3; // Present, RW
    }
    PageTable* pt = (PageTable*)(*pd_entry & ~0xFFF);

    uint64_t* pt_entry = get_pt_entry(pt, virtual_address);
    *pt_entry = ((uint64_t)physical_address) | 0x3; // Present, RW

    return 0;
}

void* translate(void* virtual_address) {
    uint64_t* pml4_entry = get_pml4_entry(virtual_address);
    if (!(*pml4_entry & 0x1)) return NULL;

    PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)(*pml4_entry & ~0xFFF);
    uint64_t* pdpt_entry = get_pdpt_entry(pdpt, virtual_address);
    if (!(*pdpt_entry & 0x1)) return NULL;

    PageDirectory* pd = (PageDirectory*)(*pdpt_entry & ~0xFFF);
    uint64_t* pd_entry = get_pd_entry(pd, virtual_address);
    if (!(*pd_entry & 0x1)) return NULL;

    PageTable* pt = (PageTable*)(*pd_entry & ~0xFFF);
    uint64_t* pt_entry = get_pt_entry(pt, virtual_address);
    if (!(*pt_entry & 0x1)) return NULL;

    return (void*)(*pt_entry & ~0xFFF);
}

void unmap_page(void* virtual_address) {
    uint64_t* pml4_entry = get_pml4_entry(virtual_address);
    if (!(*pml4_entry & 0x1)) return;

    PageDirectoryPointerTable* pdpt = (PageDirectoryPointerTable*)(*pml4_entry & ~0xFFF);
    uint64_t* pdpt_entry = get_pdpt_entry(pdpt, virtual_address);
    if (!(*pdpt_entry & 0x1)) return;

    PageDirectory* pd = (PageDirectory*)(*pdpt_entry & ~0xFFF);
    uint64_t* pd_entry = get_pd_entry(pd, virtual_address);
    if (!(*pd_entry & 0x1)) return;

    PageTable* pt = (PageTable*)(*pd_entry & ~0xFFF);
    uint64_t* pt_entry = get_pt_entry(pt, virtual_address);
    *pt_entry = 0; // Clear the entry
}
