#ifndef LCNC_KERNEL_IDT_H
#define LCNC_KERNEL_IDT_H

#include <stdint.h>
#include <stddef.h>

#ifdef __x86_64__

typedef struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t ist;          // Bits 0-2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t flags;        // Type and attributes
    uint16_t base_middle;
    uint32_t base_high;
    uint32_t zero;        // Reserved
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_pointer_t;

static struct {
    idt_entry_t entries[256];
    idt_pointer_t pointer;
} idt __attribute__((used));

#define ENTRY(X) (idt.entries[(X)])

typedef void (*idt_gate_t)(void);

extern void idt_load(uintptr_t);

void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags);

void idt_install(void);

#undef ENTRY

#endif // __x86_64__

#endif // IDT_H
