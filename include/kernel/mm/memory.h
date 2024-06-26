#ifndef LCNC_KERNEL_MM_MEMORY_H
#define LCNC_KERNEL_MM_MEMORY_H

#ifndef __HAS_STDINT
#include <stdint.h>
#define __HAS_STDINT
#endif

#ifndef __HAS_STDDEF
#include <stddef.h>
#define __HAS_STDDEF
#endif

uint8_t setupMemory();

typedef enum {
    MEMORY_REGION_SYSTEM = 0,
    MEMORY_REGION_USER = 1
} MemoryRegionType;

typedef struct MemoryRegion {
    void* base_addr;             // Base address of the memory region
    size_t size;                 // Size of the memory region
    MemoryRegionType type;       // Type of the memory region
    struct MemoryRegion* next;   // Next memory region in the linked list
} MemoryRegion;

typedef struct {
    MemoryRegion* head;          // Head of the memory region linked list
    size_t total_system_memory;  // Total system memory
    size_t total_user_memory;    // Total user memory
} MemoryManager;

// Initialize the memory manager
void init_memory_manager(MemoryManager* manager);

// Add a memory region to the manager
void add_memory_region(MemoryManager* manager, void* base_addr, size_t size, MemoryRegionType type);

// Remove a memory region from the manager
void remove_memory_region(MemoryManager* manager, void* base_addr);

// Find a memory region by address
MemoryRegion* find_memory_region(MemoryManager* manager, void* addr);



#endif
