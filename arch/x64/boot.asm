; entry.asm
BITS 64
GLOBAL _start

SECTION .text
_start:
    ; Your entry code here
    ; Call kernel main function
    extern kernel_main
    call kernel_main

    ; Halt the CPU
    cli
    hlt
