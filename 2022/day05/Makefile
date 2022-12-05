CC=gcc
CFLAGS=-Wall -pedantic -std=c99

all: main.o stack.o	
	$(CC) $(CFLAGS) main.o stack.o -o main

main: main.c
	$(CC) $(CFLAGS) -c main.c

stack: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f main *.o
