// Shared memory in C tutorial hint video
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char** argv) {

    // Pipe stuff. How to extract something from pipe written by parent

    int sharedMemoryID = atoi(argv[0]); // get shared memory id from pipe argument

    // Get a pointer to the shared memory segment
    int sharedMemoryId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); // create shared memory segment

    // Write to the shared memory segment
    *sharedMemoryPointer = 1; // write favorite number to shared memory segment

    // Detach from the shared memory segment
    shmdt(sharedMemoryPointer); // detach from shared memory segment

    return 0;
}

/* 
Summary:
get a shared memory id
called fork
the parent process does things wiht the pipe to write this sharedmemory id to the pipe
child process does some things to pass reference to the read end from that pipe to the child
calls execlp child process recieves read end of the pipe does some pipe stuff
to put the reference, actual shared memory in pipe into a local variable here
uses that to attatch to a shared memory segment like this
your child in HW 3 is then going to do some math stuff 
and based on the result its gonna write either 1 or 0 to shared memory segment
detatch itself from the shared memory segment and return
which point the parent is going to wait for the children to finish
and then attatch the shared memory segment and read the result from the shared memory segment
and then finally destroy the shared memory segment

*/