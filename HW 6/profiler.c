#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char path[64];
    char line[1024];
    char *tok[64];
    int count = 0;

    // target process id comes from the command line (defaults to 1)
    const char *pid = (argc > 1) ? argv[1] : "1";

    // --- /proc/<pid>/stat ---
    snprintf(path, sizeof(path), "/proc/%s/stat", pid);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    char *t = strtok(line, " ");
    while (t != NULL && count < 64) {
        tok[count++] = t;
        t = strtok(NULL, " ");
    }

    // --- /proc/<pid>/statm (all values in pages) ---
    char sline[256];
    char *vmem = "0";      // field 1 (total program size)
    char *shared = "0";    // field 3 (shared pages)
    snprintf(path, sizeof(path), "/proc/%s/statm", pid);
    FILE *fm = fopen(path, "r");
    if (fm != NULL && fgets(sline, sizeof(sline), fm) != NULL) {
        char *s1 = strtok(sline, " ");   // field 1 (size)
        strtok(NULL, " ");               // field 2 (resident)
        char *s3 = strtok(NULL, " ");    // field 3 (shared)
        if (s1 != NULL) vmem = s1;
        if (s3 != NULL) shared = s3;
    }
    if (fm != NULL) fclose(fm);

    printf("Executable name: %s\n", tok[1]);   // stat field 2
    printf("PPID: %s\n",            tok[3]);    // stat field 4
    printf("PGRP: %s\n",            tok[4]);    // stat field 5
    printf("State: %s\n",           tok[2]);    // stat field 3
    printf("User mode: %s\n",       tok[13]);   // stat field 14
    printf("Kernel mode: %s\n",     tok[14]);   // stat field 15
    printf("Virtual memory: %s\n",  vmem);      // statm field 1 (pages)
    printf("Resident pages: %s\n",  tok[23]);   // stat field 24
    printf("Shared pages: %s\n",    shared);    // statm field 3
    printf("Page faults: %s\n",     tok[11]);   // stat field 12

    return EXIT_SUCCESS;
}