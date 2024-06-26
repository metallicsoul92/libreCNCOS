#ifndef LCNC_KERNEL_PAGING_H
#define LCNC_KERNEL_PAGING_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_ENTRIES 512 // for x86_64

typedef uint64_t PageTableEntry;

typedef struct PageTable {
    PageTableEntry entries[PAGE_TABLE_ENTRIES];
} PageTable;

typedef PageTable PageDirectory;
typedef PageTable PageDirectoryPointerTable;
typedef PageTable PageMapLevel4;

void setup_paging();
int map_page(void* virtual_address, void* physical_address);
void* translate(void* virtual_address);
void unmap_page(void* virtual_address);

#endif // LCNC_KERNEL_PAGING_H
