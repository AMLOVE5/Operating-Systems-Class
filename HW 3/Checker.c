#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    // arg[1] is the divisor, arg[2] is the dividend
    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);

    // Pipe stuff. How to extract something from pipe written by parent
    int fd = atoi(argv[3]);
    int sharedMemoryId;
    read(fd, &sharedMemoryId, sizeof(sharedMemoryId)); // read favorite number from pipe
    printf("Checker process [%d]: read 4 bytes containing shm ID %d.\n", getpid(), sharedMemoryId); // print
    close(fd);
    // Get a pointer to the shared memory segment
    int *sharedMemoryPointer = (int*)shmat(sharedMemoryId, NULL, 0); // attach to shared memory segment
    printf("Checker process [%d] : Starting. \n", getpid()); //from ex output

    if (dividend%divisor == 0) { //is divisible
        printf("Checker process [%d]: %d *IS* divisible by %d. \n", getpid(), dividend, divisor);
        *sharedMemoryPointer = 1; // write favorite number to shared memory segment
        printf("Checker process [%d]: wrote result (1) to shared memory. \n", getpid());
    }
    else { // not divisible
        printf("Checker process [%d]: %d *IS NOT* divisible by %d. \n", getpid(), dividend, divisor);
        *sharedMemoryPointer = 0; // write favorite number to shared memory segment
        printf("Checker process [%d]: wrote result (0) to shared memory. \n", getpid());
    }
    // Detach from the shared memory segment
    shmdt(sharedMemoryPointer); // detach from shared memory segment
    return 0;
}