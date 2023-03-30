#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <stdio.h>

ssize_t my_write(int fd, const char* buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

int main() {

    if (my_write(1, "Hello world!\n", 13) < 0) {
	perror("my_write");
     	return -1;
    }

    return 0;
}
