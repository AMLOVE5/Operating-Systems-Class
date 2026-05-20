README
======

This package includes the following files.

|-- Driver.c [This is the driver program which will be used to invoke the MemoryManager.]
|-- MemoryManager.c [MemoryManager is implemented here.]
|-- MemoryManager.h [Header file declaring the function exposed from MemoryManager]
|-- README.txt [This file]

The following files are new.
|-- Makefile [This is per the instructions. It performs make clean and make all]

Compile:
    make build
Run:
    ./a.out <seed>
For example;
    ./a.out 1234
Clean:
    make clean