.data

hello:
    .ascii "Hello, world!\n"
    length = . - hello

.text
    .global _start

_start:
    movq $1, %rax
    movq $1, %rdi
    movq $hello, %rsi
    movq $length, %rdx
    syscall

    movq $60, %rax
    xorq %rdi, %rdi
    syscall
