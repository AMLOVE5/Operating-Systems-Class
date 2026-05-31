// Pipes in C tutorial hint video
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {

    int fd = atoi(argv[0]);
    int fav_number = atoi(argv[0]);

    read(fd, &fav_number, sizeof(fav_number)); // read favorite number from pipe
    printf("Input from pipe: %d\n", fav_number); // print the favorite number read from the pipe

    return 0;
}
