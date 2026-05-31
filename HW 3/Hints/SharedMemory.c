// Shared memory in C tutorial hint video
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 

int main() {

    int sharedMemoryId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); // create shared memory segment

    // Fork

    // Parent process handling 
        // Pipe stuff. Passing shared memory id to child process through pipe

    // Child process handling
        // Get the sharedMemoryId from the pipe
        // Using pipes
        // Using execlp

    // Wait for child process to finish

    // Attatch to shared memory segment
    int *sharedMemoryPointer = (int*)shmat(sharedMemoryId, NULL, 0); // attach to shared memory segment

    // Read from the shared memory segment

    // Destrong the shared memory segment
    shmctl(*sharedMemoryPointer, IPC_RMID, NULL); // destroy shared memory segment
    return 0;
}