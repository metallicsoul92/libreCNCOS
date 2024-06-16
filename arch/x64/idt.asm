global idt_load
section .text

idt_load:
    ; Load IDT
    lidt [rdi]
    ret
