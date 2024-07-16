#include "../../include/kernel/mm/kmalloc.h"
#include "../../include/kernel/mm/memory.h"
#include "../../include/kernel/mm/pmm.h"
#include "../../include/kernel/paging.h"

// Declaration of the 'end' symbol defined in the linker script
extern uint8_t end;

uint8_t setupMemory(void) {
    /* Calculate total memory */
    size_t total_memory = 1024 * 1024 * 10; // 10MB to start with

    // Initialize physical memory manager (pmm)
    init_pmm(total_memory);

    // Setup paging structures
    setup_paging();

    // Initialize heap with the address immediately following the kernel
    uint8_t* heap_start = &end;
    init_heap(heap_start);

    return 0; // Return success
}



void init_memory_manager(MemoryManager* manager) {
    manager->head = NULL;
    manager->total_system_memory = 0;
    manager->total_user_memory = 0;
}

void add_memory_region(MemoryManager* manager, void* base_addr, size_t size, MemoryRegionType type) {
    MemoryRegion* new_region = (MemoryRegion*)kmalloc(sizeof(MemoryRegion));
    if (new_region == NULL) {
        // Handle allocation failure
        return;
    }
    new_region->base_addr = base_addr;
    new_region->size = size;
    new_region->type = type;
    new_region->next = manager->head;
    manager->head = new_region;

    if (type == MEMORY_REGION_SYSTEM) {
        manager->total_system_memory += size;
    } else {
        manager->total_user_memory += size;
    }
}

void remove_memory_region(MemoryManager* manager, void* base_addr) {
    MemoryRegion* prev = NULL;
    MemoryRegion* curr = manager->head;

    while (curr != NULL) {
        if (curr->base_addr == base_addr) {
            if (prev == NULL) {
                manager->head = curr->next;
            } else {
                prev->next = curr->next;
            }

            if (curr->type == MEMORY_REGION_SYSTEM) {
                manager->total_system_memory -= curr->size;
            } else {
                manager->total_user_memory -= curr->size;
            }

            kfree(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

MemoryRegion* find_memory_region(MemoryManager* manager, void* addr) {
    MemoryRegion* curr = manager->head;
    while (curr != NULL) {
        if (addr >= curr->base_addr && addr < (curr->base_addr + curr->size)) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
