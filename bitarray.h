#ifndef BLOOMFILTERC_BITARRAY_H
#define BLOOMFILTERC_BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _bitarray {
    unsigned char *array;
    int size;
} bitarray;

/* Return a pointer to an empty bitarray that can store m bits */
bitarray *create_bitarray(int m);

/* Free the memory associated with the bitarray */
void free_bitarray(bitarray *a);

/* Set position pos in the bitarray to 1 */
void set_bitarray(bitarray *a, int pos);

/* Set position pos in the bitarray to 0 */
void reset_bitarray(bitarray *a, int pos);

/* Get the value at position pos in the bitarray */
int get_bitarray(bitarray *a, int pos);

/* Set all positions in the bitarray to 0 */
void clear_bitarray(bitarray *a);

#endif /* BLOOMFILTERC_BITARRAY_H */
