section .text
global load_page_directory
global enable_paging

load_page_directory:
    mov rax, [rsp + 8]  ; Get the address of the page directory
    mov cr3, rax        ; Load it into CR3
    ret

enable_paging:
    mov rax, cr0
    bts rax, 31          ; Set the paging bit (bit 31)
    mov cr0, rax
    ret
