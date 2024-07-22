#ifndef LCNC_LOADER_PMODESTRUCTS_H
#define LCNC_LOADER_PMODESTRUCTS_H

#ifndef __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#define __HAS_STDINT
#endif


// Define a GDT entry for 32-bit
struct gdt_entry_32 {
    uint16_t limit_low;     // Lower 16 bits of the limit
    uint16_t base_low;      // Lower 16 bits of the base
    uint8_t base_middle;    // Next 8 bits of the base
    uint8_t access;         // Access flags, determine what ring this segment can be used in
    uint8_t granularity;
    uint8_t base_high;      // Last 8 bits of the base
} __attribute__((packed));


// Define the GDT pointer structure
struct gdt_ptr_32{
    uint16_t limit;         // The upper 16 bits of all selector limits
    uint32_t base;          // The address of the first gdt_entry_32 struct
} __attribute__((packed));

typedef struct gdt_entry_32 gdtEntry32_t;
typedef struct gdt_ptr_32 gdtPtr32_t;

void set_gdt_entry_32(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void init_gdt_32();

typedef uint64_t page_entry_t;

void setup_pml4(page_entry_t *pml4);
page_entry_t* get_pml4_table();

void setup_pml5(page_entry_t *pml5);
page_entry_t* get_pml5_table();
int is_pml5_supported();



#endif
