README
======
 
This package includes the following files.
 
|-- Scheduler.c [Main source file. Implements FCFS (non-preemptive), SJF
               (preemptive), and priority (preemptive) scheduling, and prints
               average turnaround time, average waiting time, and throughput
               for each. Reads the process list from the input file given on
               the command line.]
|-- profiler.c [Reads /proc/<pid>/stat and /proc/<pid>/statm for the process id
               given on the command line and prints executable name, PPID,
               PGRP, state, user-mode time, kernel-mode time, virtual memory,
               resident pages, shared pages, and page faults.]
|-- README.txt [This file]
|-- Makefile [Builds both executables. Targets: build, clean.]
 
Compile:
    make build
Run:
    ./Scheduler <input_filename>
    ./profiler <pid>
For example;
    ./Scheduler input.txt
    ./profiler 1
Clean:
    make clean