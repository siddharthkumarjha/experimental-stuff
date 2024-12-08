.global _start
.section .text
_start:
        mov $1, %rax #tell processor a write op is gonna happen
        mov $1, %rdi #we are gonna use stdout
        mov $msg, %rsi #push message to rsi
        mov $13, %rdx #tell rdx the size of message
        syscall #call kernel to do a thing...

        mov $60, %rax #tell processor to exit the program
        mov $0, %rdi #give exit code as 0
        syscall #again call the kernel

msg:
        .asciz "Hello World!\n" #write our message
