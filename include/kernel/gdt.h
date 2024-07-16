#ifndef LCNC_KERNEL_GDT_H
#define LCNC_KERNEL_GDT_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

// Define a GDT entry for 64-bit
struct gdt_entry_64 {
    uint16_t limit_low;     // Lower 16 bits of the limit
    uint16_t base_low;      // Lower 16 bits of the base
    uint8_t base_middle;    // Next 8 bits of the base
    uint8_t access;         // Access flags
    uint8_t granularity;    // Granularity and other flags
    uint8_t base_high;      // Last 8 bits of the base
} __attribute__((packed));

// Define a GDT pointer structure for 64-bit
struct gdt_ptr_64 {
    uint16_t limit;         // The upper 16 bits of all selector limits
    uint64_t base;          // The address of the first gdt_entry_64 struct
} __attribute__((packed));

typedef struct gdt_entry_64 gdtEntry64_t;
typedef struct gdt_ptr_64 gdtPtr64_t;

#endif // LCNC_KERNEL_GDT_H
