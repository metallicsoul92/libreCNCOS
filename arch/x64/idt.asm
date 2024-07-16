; idt_load.asm
global idt_load
section .text

idt_load:
    ; Takes a pointer to the IDT descriptor
    mov rax, [rsp+8] ; Get the argument passed to the function (IDT pointer)
    lidt [rax]       ; Load IDT
    ret
