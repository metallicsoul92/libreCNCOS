section .text
global inb, inw, inl, inq
global outb, outw, outl, outq

; Read a byte from the specified I/O port
inb:
    mov dx, di         ; Load port number into dx
    in al, dx          ; Read byte from port into al
    movzx rax, al      ; Zero-extend al to rax
    ret

; Read a word (2 bytes) from the specified I/O port
inw:
    mov dx, di         ; Load port number into dx
    in ax, dx          ; Read word from port into ax
    movzx rax, ax      ; Zero-extend ax to rax
    ret

; Read a double word (4 bytes) from the specified I/O port
inl:
    mov dx, di         ; Load port number into dx
    in eax, dx         ; Read dword from port into eax
    ret

; Read a quad word (8 bytes) from the specified I/O port
inq:
    ; Reading 64 bits from an I/O port is non-standard and typically not supported
    ; This function will read two consecutive double words and combine them
    mov dx, di         ; Load port number into dx
    in eax, dx         ; Read first dword from port into eax
    mov r8d, eax       ; Store first dword in r8d
    add dx, 4          ; Increment port number by 4
    in eax, dx         ; Read second dword from port into eax
    shl rax, 32        ; Shift second dword left by 32 bits
    or rax, r8         ; Combine with first dword
    ret

; Write a byte to the specified I/O port
outb:
    mov dx, di         ; Load port number into dx
    mov al, sil        ; Load value into al
    out dx, al         ; Write byte to port
    ret

; Write a word (2 bytes) to the specified I/O port
outw:
    mov dx, di         ; Load port number into dx
    mov ax, si         ; Load value into ax
    out dx, ax         ; Write word to port
    ret

; Write a double word (4 bytes) to the specified I/O port
outl:
    mov dx, di         ; Load port number into dx
    mov eax, esi       ; Load value into eax
    out dx, eax        ; Write dword to port
    ret

; Write a quad word (8 bytes) to the specified I/O port
outq:
    ; Writing 64 bits to an I/O port is non-standard and typically not supported
    ; This function will write two consecutive double words
    mov dx, di         ; Load port number into dx
    mov eax, esi       ; Load lower dword into eax
    out dx, eax        ; Write lower dword to port
    add dx, 4          ; Increment port number by 4
    shr rsi, 32        ; Shift upper dword into lower 32 bits
    mov eax, esi       ; Load upper dword into eax
    out dx, eax        ; Write upper dword to port
    ret
