#include "../include/kernel/idt.h"

void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
    ENTRY(num).base_low = (uint16_t)((uintptr_t)base & 0xFFFF);
    ENTRY(num).base_middle = (uint16_t)(((uintptr_t)base >> 16) & 0xFFFF);
    ENTRY(num).base_high = (uint32_t)(((uintptr_t)base >> 32) & 0xFFFFFFFF);
    ENTRY(num).sel = sel;
    ENTRY(num).ist = 0;   // No IST
    ENTRY(num).flags = flags | 0x60;
    ENTRY(num).zero = 0;
}

void idt_install(void) {
    idt_pointer_t *idtp = &idt.pointer;
    idtp->limit = sizeof(idt.entries) - 1;
    idtp->base = (uint64_t)&idt.entries;

    for (size_t i = 0; i < sizeof(idt.entries) / sizeof(idt.entries[0]); i++) {
        memset(&idt.entries[i], 0, sizeof(idt.entries[0]));
    }

    idt_load((uintptr_t)idtp);
}
