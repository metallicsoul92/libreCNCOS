; loader.asm
BITS 32
GLOBAL _start
EXTERN lmain
EXTERN setup_pml4
EXTERN setup_pml5
EXTERN is_pml5_supported
EXTERN map_page
EXTERN map_page_pml5

SECTION .multiboot
ALIGN 4
magic:          dd 0x1BADB002        ; Magic number
flags:          dd 0x00000003        ; Flags
checksum:       dd -(magic + flags)  ; Checksum

start:
    ; Setup stack
    mov esp, 0x9FB00

    ; Enable A20 line
    in al, 0x64
    or al, 2
    out 0x64, al

    ; Enable PAE
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; Setup GDT
    call init_gdt_32
