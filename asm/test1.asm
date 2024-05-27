global _start

section .data
msg db "hellow", 10
msglen equ $-msg 

section .text
_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, msglen
    syscall

    mov rax, 60
    syscall
