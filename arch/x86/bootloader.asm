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

_start:
    ; Set up stack
    mov esp, 0x9FB00

    ; Enable A20 line
    in al, 0x64
    or al, 2
    out 0x64, al

    ; Enable PAE
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; Check for PML5 support
    call is_pml5_supported
    test eax, eax
    jz setup_pml4_mode

    ; PML5 setup
    call setup_pml5

    ; Map pages using PML5
    ; Example mapping
    ; call map_page_pml5, [pml5, virt_addr, phys_addr, flags]

    jmp setup_complete

setup_pml4_mode:
    ; PML4 setup
    call setup_pml4

    ; Map pages using PML4
    ; Example mapping
    ; call map_page, [pml4, virt_addr, phys_addr, flags]

setup_complete:
    ; Load PML4 or PML5 address into CR3
    mov eax, pml4_table_or_pml5_table
    mov cr3, eax

    ; Enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x100
    wrmsr

    ; Enable paging
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; Far jump to long mode
    jmp 0x08:long_mode_entry_point

BITS 64
SECTION .text
long_mode_entry_point:
    ; Set up segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Call the C main function (64-bit)
    call lmain

hang:
    hlt
    jmp hang
