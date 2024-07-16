#include "../../libc/crt/include/stddef.h"   // For size_t, NULL
#include "../../libc/crt/include/stdint.h"   // For uint8_t
#include "../../include/kernel/syscalls.h"
#include "../../include/kernel/mm/kmalloc.h"

// Assume HEAP_START is the initial start of your heap area
extern uint8_t HEAP_START[];

// Global variable to track the end of the heap
static uint8_t* heap_end = HEAP_START;

void* sbrk(ptrdiff_t increment) {
    void* old_heap_end = heap_end;

    if (increment > 0) {
        // Increase the heap
        heap_end += increment;
    } else if (increment < 0) {
        // Decrease the heap (not supported in basic implementation)
        // Optionally handle freeing memory
        return (void*)-1; // Error: not supported
    }

    return old_heap_end;
}
