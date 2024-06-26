#ifndef LCNC_KERNEL_IDT_H
#define LCNC_KERNEL_IDT_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include <stdint.h>
#endif


// Structure for an IDT entry
typedef struct {
    uint16_t offset_low;    // Lower 16 bits of handler function address
    uint16_t selector;      // Kernel segment selector
    uint8_t ist;            // Bits 0-2 hold Interrupt Stack Table offset, rest are zero
    uint8_t type_attr;      // Type and attributes
    uint16_t offset_middle; // Middle 16 bits of handler function address
    uint32_t offset_high;   // Higher 32 bits of handler function address
    uint32_t zero;          // Reserved, set to zero
} __attribute__((packed)) idt_entry_t;

// Structure for the IDT pointer
typedef struct {
    uint16_t limit; // Limit of the table (size - 1)
    uint64_t base;  // Base address of the IDT
} __attribute__((packed)) idt_ptr_t;

// Function declarations
void idt_set_gate(int num, uint64_t base, uint16_t sel, uint8_t flags);
void idt_install();

#endif // IDT_H
