.section .rodata
msg:
    .asciz "Hello, World\n"
msg_len = . - msg

.global _start
.section .text
_start:
mov $1, %rax
mov $1, %rdi
mov $msg, %rsi
mov $msg_len, %rdx
syscall

mov $60, %rax
mov $0, %rdi
syscall
