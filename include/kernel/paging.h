#ifndef LCNC_KERNEL_PAGING_H
#define LCNC_KERNEL_PAGING_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

#define PAGE_SIZE 4096

typedef uint64_t page_entry_t;

typedef struct {
    page_entry_t entries[512];
} __attribute__((aligned(PAGE_SIZE))) PageMapLevel4;

typedef struct {
    page_entry_t entries[512];
} __attribute__((aligned(PAGE_SIZE))) PageDirectoryPointerTable;

typedef struct {
    page_entry_t entries[512];
} __attribute__((aligned(PAGE_SIZE))) PageDirectory;

typedef struct {
    page_entry_t entries[512];
} __attribute__((aligned(PAGE_SIZE))) PageTable;

void setup_paging(void);
int map_page(void* virtual_address, void* physical_address);
void* translate(void* virtual_address);
void unmap_page(void* virtual_address);

#endif // LCNC_KERNEL_PAGING_H
