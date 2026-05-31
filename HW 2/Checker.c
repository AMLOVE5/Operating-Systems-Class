#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // arg[1] is the divisor, arg[2] is the dividend
    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);
    printf("Checker process [%d] : Starting. \n", getpid()); //from ex output
    if (dividend%divisor == 0) { // is divisible
        printf("Checker process [%d]: %d *IS* divisible by %d. \n", getpid(), dividend, divisor);
        printf("Checker process [%d]: Returning 1. \n", getpid());
        return 1;
    }
    else { // not divisible
        printf("Checker process [%d]: %d *IS NOT* divisible by %d. \n", getpid(), dividend, divisor);
        printf("Checker process [%d]: Returning 0. \n", getpid());
        return 0;
    }
}
