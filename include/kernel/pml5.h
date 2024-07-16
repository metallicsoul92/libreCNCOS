// pml5.h

#ifndef LCNC_KERNEL_PML5_H
#define LCNC_KERNEL_PML5_H

#include "pml4.h"

#define PML5_SIZE 512
#define PML5_ENTRY(addr) ((addr >> 48) & 0x1FF)

void setup_pml5(page_entry_t *pml5);
int is_pml5_supported();

#endif // PML5_H
