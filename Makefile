CC=gcc
CFLAGS=-I.
DEPS = record.h prototypes.h

%.o: %.c $(DEPS)
	$(CC) -lm -pedantic-errors -Wall -c -o $@ $< $(CFLAGS)

progassign1: main.o functions.o
	gcc -lm -o progassign1 main.o functions.o $(CFLAGS)
