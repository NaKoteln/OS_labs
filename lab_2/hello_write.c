#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

    if (write(1, "Hello world!\n", 13) < 0) {
    	perror("write");
	return -1;
    }

    return 0;
}
