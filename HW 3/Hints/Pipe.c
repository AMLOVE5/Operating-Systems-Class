// Pipes in C tutorial hint video
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    int fd[2];
    pipe(fd); // fd[0] is read end, fd[1] is write end

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    }

    else if (pid > 0) {
        close(fd[0]); // close read end in parent
        int fav_number = 42;
        write(fd[1], &fav_number, sizeof(int)); // write favorite number to pipe
        close(fd[1]); // close write end in parent
    }

    else {
        char buffer[8];
        sprintf(buffer, "%d", fd[0]); // sprintf syntax formatting the read end of the pipe into a string buffer
        execlp("child", buffer, NULL); // execute child program with the read end of the pipe as argument
    }

    return 0;
}