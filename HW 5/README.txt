README
======
This package includes the following files.

|-- Scheduler.cc  [Implements FCFS (non-preemptive), SJF Preemptive (SRTF), and Priority Preemptive CPU scheduling algorithms. 
Reports average turnaround time, average waiting time, and throughput for each.]
|-- Makefile      [This is per the instructions. Compiles Scheduler.cc into the Scheduler executable.]
|-- README.txt    [This file]

Compile:
    make

Run:
    ./Scheduler <input_filename>

For example:
    ./Scheduler CS370-HW5-Input.csv

Clean:
    make clean