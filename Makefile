CC=gcc
CFLAGS=-std=c99 -Wall -g
OBJS=8cc.o string.o list.o gen.o read.o file.o

8cc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJS): 8cc.h

tests: tests.o string.o list.o gen.o file.o 8cc.h
	$(CC) $(CFLAGS) -o $@ string.o list.o gen.o tests.o file.o 

clean:
	-rm -f 8cc $(OBJS) *.o hello tests

hello: 8cc
	echo 'main() {printf("Hello, world!\n");}' | ./8cc - hello.o
	$(CC) -o hello hello.o

test: hello tests
	@./runtest

all: 8cc
