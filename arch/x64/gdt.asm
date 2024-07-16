; gdt.asm
BITS 64

section .data
gdt_start:
    dq 0x0000000000000000 ; Null segment
    dq 0x00af9a000000ffff ; Code segment descriptor
    dq 0x00cf92000000ffff ; Data segment descriptor
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Limit (size of GDT - 1)
    dq gdt_start                ; Base (address of GDT)

section .text
global load_gdt
load_gdt:
    ; Load the GDT descriptor
    lgdt [gdt_descriptor]

    ; Update the segment registers (these will be ignored in long mode)
    mov ax, 0x10              ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Jump to the next instruction in the new code segment
    jmp load_code_segment     ; Regular jump to the next code segment

load_code_segment:
    ; Execution continues here in the new code segment
    ret

section .text
global gdt_flush

; gdt_flush function to load the new GDT
gdt_flush:
    ; Load the address of the GDT into the GDTR register
    lgdt [rsp + 8]

    ; Update segment registers
    mov ax, 0x10              ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Jump to the flush_done
    jmp flush_done

flush_done:
    ret
