#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    // arg[1] is divisor, arg[2...5] are dividends = 5 arguments
    char *divisor = argv[1];
    pid_t pid[argc];
    int sharedMemoryId[argc];
    int fd[argc][2];
    for(int i = 2; i < argc; i++) {
        pipe(fd[i]); // fd[0] is read end, fd[1] is write end

        int sharedMemoryIdTemp = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); // create shared memory segment
        sharedMemoryId[i] = sharedMemoryIdTemp;

        // Fork
        pid[i] = fork();

        // parent
        if (pid[i] > 0) {
            // Parent process handling 
                // Pipe stuff. Passing shared memory id to child process through pipe
            close(fd[i][0]); // close read end in parent
            printf("Coordinator: forked process with ID %d.\n", pid[i]);
            int bytesWritten = write(fd[i][1], &sharedMemoryId[i], sizeof(int)); // write favorite number to pipe
            printf("Coordinator: wrote shm ID %d to pipe (%d bytes).\n", sharedMemoryId[i], bytesWritten);
            close(fd[i][1]); // close write end in parent
        }

        // child
        else {
            // Child process handling
                // Get the sharedMemoryId from the pipe
                // Using pipes
                // Using execlp
            close(fd[i][1]); // close write end in child
            char buffer[8];
            sprintf(buffer, "%d", fd[i][0]); // sprintf syntax formatting the read end of the pipe into a string buffer
            // match exec 2 in makefile
            execlp("./checker", "checker", divisor, argv[i], buffer, NULL);
        }
    }

    for(int i = 2; i < argc; i++) {
        // Wait for child process to finish
        printf("Coordinator: waiting on child process ID %d...\n", pid[i]);
        int status;
        waitpid(pid[i], &status, 0);
        // Attatch to shared memory segment
        int *sharedMemoryPointer = (int*)shmat(sharedMemoryId[i], NULL, 0); // attach to shared memory segment
        // Read from the shared memory segment
        int result = *sharedMemoryPointer;
        if (result == 1) {
            printf("Coordinator: result %d read from shared memory: %s is divisible by %s.\n", result, argv[i], divisor);
        }
        else {
            printf("Coordinator: result %d read from shared memory: %s is not divisible by %s.\n", result, argv[i], divisor);
        }
        shmdt(sharedMemoryPointer);
        // Destrong the shared memory segment
        shmctl(sharedMemoryId[i], IPC_RMID, NULL); // destroy shared memory segment
    }

    printf("Coordinator: exiting.\n");
    return 0;
}