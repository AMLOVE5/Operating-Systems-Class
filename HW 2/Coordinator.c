#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // arg[1] is divisor, arg[2...5] are dividends = 5 arguments
    char *divisor = argv[1];
    for(int i = 2; i < argc; i++) {
        pid_t pid = fork();
        // failed case
        if (pid == -1) {
            printf("Fork failed.\n");
        }
        // child
        else if (pid == 0) {
            // match exec 2 in makefile
            execlp("./checker", "checker", divisor, argv[i], NULL);
        }
        // parent
        else {
            printf("Coordinator: forked process with ID %d.\n", pid);
            printf("Coordinator: waiting for process [%d].\n", pid);
            int status;
            wait(&status);
            int result = WEXITSTATUS(status);
            printf("Coordinator: child process %d returned %d.\n", pid, result);
        }
    }
    printf("Coordinator: exiting.\n");
    return 0;
}