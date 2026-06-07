README
======

This package includes the following files.

|-- BoundedBuffer.java [A thread-safe circular FIFO buffer backed by an array of doubles.
Supports store() and retrieve() methods synchronized using wait() and notifyAll().]
|-- Producer.java [Produces 1,000,000 random Double values and stores them in the
BoundedBuffer. Prints cumulative value every 100,000 items.]
|-- Consumer.java [Consumes 1,000,000 Double values from the BoundedBuffer.
Prints cumulative value every 100,000 items.]
|-- ProducerConsumer.java [Entry point. Creates one shared BoundedBuffer, one Producer,
and one Consumer, runs them on separate threads, and waits for both to finish.]
|-- Makefile [Compiles and runs the program.]
|-- README.txt [This file]

Compile:
    make all
Run:
    make run
Clean:
    make clean 