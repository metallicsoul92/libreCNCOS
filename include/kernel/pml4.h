// pml4.h

#ifndef LCNC_KERNEL_PML4_H
#define LCNC_KERNEL_PML4_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4

#define PML4_SIZE 512
#define PML4_ENTRY(addr) ((addr >> 39) & 0x1FF)
#define PDPT_ENTRY(addr) ((addr >> 30) & 0x1FF)
#define PD_ENTRY(addr) ((addr >> 21) & 0x1FF)
#define PT_ENTRY(addr) ((addr >> 12) & 0x1FF)

#ifndef __HAS_PAGE_ENTRY_T
typedef uint64_t page_entry_t;
#define __HAS_PAGE_ENTRY_T 1
#endif

void setup_pml4(page_entry_t *pml4);
void map_page(page_entry_t *pml4, uint64_t virt_addr, uint64_t phys_addr, uint64_t flags);

#endif // PML4_H
