CC=gcc
build: Scheduler profiler
Scheduler: Scheduler.c
	$(CC) -o Scheduler Scheduler.c
profiler: profiler.c
	$(CC) -o profiler profiler.c
clean:
	rm -f *.o Scheduler profiler
# Packages directory files into .zip file
package:
	zip -r Love-Annamarie-HW5.zip Scheduler.c profiler.c Makefile README.txt