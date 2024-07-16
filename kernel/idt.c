#include "../include/kernel/idt.h"

// IDT with 256 entries
idt_entry_t idt[256];
idt_ptr_t idt_ptr;

// Set an entry in the IDT
void idt_set_gate(int num, uint64_t base, uint16_t sel, uint8_t flags) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].ist = 0;
    idt[num].type_attr = flags;
    idt[num].offset_middle = (base >> 16) & 0xFFFF;
    idt[num].offset_high = (base >> 32) & 0xFFFFFFFF;
    idt[num].zero = 0;
}

// Load the IDT
extern void idt_load(uint64_t);

void idt_install() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint64_t)&idt;

    // Set each entry here
    // Example: idt_set_gate(32, (uint64_t)isr32, 0x08, 0x8E);

    idt_load((uint64_t)&idt_ptr);
}
