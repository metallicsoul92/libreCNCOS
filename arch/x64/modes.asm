section .text
bits 16
global enter_protected_mode
global enter_long_mode
extern pm_main
extern lm_main

enter_protected_mode:
    cli                 ; Clear interrupts

    ; Setup the GDT
    lgdt [gdt_descriptor]

    ; Enable protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump to clear prefetch queue and switch to protected mode
    jmp 0x08:protected_mode_entry

bits 32
protected_mode_entry:
    ; Update segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Now we are in protected mode, call C function
    call pm_main

    ; Halt if pm_main returns
halt_pm:
    hlt
    jmp halt_pm

enter_long_mode:
    cli                 ; Clear interrupts

    ; Setup the PML4 table
    ; (Assume the tables are already setup correctly)

    ; Load PML4 address into CR3
    mov eax, cr3_addr
    mov cr3, eax

    ; Enable PAE (Physical Address Extension)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enable paging
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; Far jump to clear prefetch queue and switch to long mode
    jmp 0x08:long_mode_entry

bits 64
long_mode_entry:
    ; Update segment registers with long mode segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Now we are in long mode, call C function
    call lm_main

    ; Halt if lm_main returns
halt_lm:
    hlt
    jmp halt_lm

section .data
gdt:
    dq 0x0000000000000000  ; Null descriptor
    dq 0x00AF9A000000FFFF  ; Code segment
    dq 0x00AF92000000FFFF  ; Data segment

gdt_descriptor:
    dw gdt_end - gdt - 1   ; Limit
    dd gdt                 ; Base

gdt_end:

cr3_addr:
    dd 0x100000
