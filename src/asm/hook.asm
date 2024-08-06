; hook.asm
option casemap:none

.code
trampoline PROC
    ; Save the registers
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    sub rsp, 8


    ; Restore the registers
    add rsp, 8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; Jump to the original function
    jmp rax
trampoline ENDP

END
