README
======

This package includes the following files.

|-- Checker.c [This is the program that checks if the input's divisors and dividends are divisible.]
|-- Coordinator.c [This coordinates fork(), wait(), and exec() commands following the logic of parent and child.]
|-- Checker.h [Header file declaring the function exposed from Checker.]
|-- Makefile [This is per the instructions. It performs make clean]
|-- README.txt [This file]

Compile:
    make build
Run:
    ./coordinator <divisor> <dividend1> <dividend2> <dividend3> <dividend4>
For example;
    ./coordinator 3 8 15 21 45
Clean:
    make clean