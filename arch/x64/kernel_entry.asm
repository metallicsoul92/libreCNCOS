section .text
bits 64
global long_mode_entry
extern kernel_main

long_mode_entry:
    ; Update segment registers with long mode segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Now we are in long mode, call C function
    call kernel_main

    ; Halt if kernel_main returns
halt_lm:
    hlt
    jmp halt_lm
