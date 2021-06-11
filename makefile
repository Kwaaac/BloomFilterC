CC=gcc
CFLAGS=-Wall -ansi -g
LDFLAGS= -lm
DEPS=bitarray.h filter.h hashtable.h
OBJ=bitarray.o filter.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

main_test_hash: main_test_hash.o hashtable.o
	gcc -o $@ $^ $(LDFLAGS)

test: test.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) test main test.o main.o
