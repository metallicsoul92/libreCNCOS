#include "../../include/kernel/mm/pmm.h"     // for alloc_page
#include "../../include/kernel/paging.h"     // for map_page
#include "../../libc/crt/include/string.h"   // for memset
#include "../../libc/crt/include/stdbool.h"  // For bool, true, false
#include "../../libc/crt/include/stdint.h"   // For uintptr_t
#include "../../libc/crt/include/stddef.h"   // For size_t, NULL
#include "../../libc/posix/include/sys/types.h" //For off_t

#define PAGE_SIZE 4096  // Example page size, adjust as per your system

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
    // Round length up to nearest page size
    size_t num_pages = (length + PAGE_SIZE - 1) / PAGE_SIZE;

    // Allocate virtual memory space
    void* start_addr = addr;
    for (size_t i = 0; i < num_pages; ++i) {
        // Allocate physical memory page
        void* phys_page = alloc_page();
        if (phys_page == NULL) {
            // Handle allocation failure
            return MAP_FAILED;
        }

        // Map virtual address to physical address
        map_page(start_addr + i * PAGE_SIZE, phys_page);

        //Clear the allocated memory
         memset(start_addr + i * PAGE_SIZE, 0, PAGE_SIZE);
    }

    return start_addr;
}
