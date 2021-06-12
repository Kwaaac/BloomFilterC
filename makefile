CC=gcc
CFLAGS=-Wall -ansi -g
LDFLAGS= -lm
DEPS=bitarray.h filter.h
OBJ=bitarray.o filter.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

main_test_hash: main_test_hash.o hashtable.o hashtable.h
	gcc -o $@ $^ $(LDFLAGS)

main_test_bst: main_test_bst.o tree_word.o tree_word.h
	gcc -o $@ $^ $(LDFLAGS)

main_false_positive: test_false_positive.o hashtable.o hashtable.h $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

test: test.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) test main main.o main_test_hash main_test_hash.o hashtable.o main_test_bst main_test_bst.o tree_word.o main_false_positive test_false_positive.o test test.o
