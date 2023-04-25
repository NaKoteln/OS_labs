#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <syscall.h>

ssize_t my_write(int fd, const void *buf, size_t count) {
    ssize_t result;
    asm volatile (
            "movq %4, %%rax\n" // номер системного вызова write
            "movq %1, %%rdi\n" // аргумент fd
            "movq %2, %%rsi\n" // аргумент buf
            "movq %3, %%rdx\n" // аргумент count
            "syscall\n"        // выполнение системного вызова
            "movq %%rax, %0\n" // сохранение результата в переменную result
            : "=r" (result)    // выходной операнд
            : "r" ((long)fd), "r" (buf), "r" (count), "r" ((long)SYS_write) // входные операнды
            : "%rax", "%rdi", "%rsi", "%rdx" // используемые регистры
            );

    if (result < 0) {
        errno = -result;
    }

    return result;
}

int main() {
    char buf[] = "Hello, world!\n";
    if (my_write(STDOUT_FILENO, buf, sizeof(buf)) < 0) {
        perror("my_write");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}