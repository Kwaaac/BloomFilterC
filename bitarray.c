
#include "bitarray.h"

bitarray *create_bitarray(int m) {
    bitarray *new_bitarray = (bitarray *) malloc(sizeof(bitarray));

    assert(new_bitarray != NULL);

    new_bitarray->size = m;
    new_bitarray->array = (unsigned char *) calloc(m, sizeof(unsigned char));
    assert(new_bitarray->array != NULL);

    return new_bitarray;
}

void free_bitarray(bitarray *a) {
    free(a->array);
    free(a);
}

/* Set position pos in the bitarray to 1 */
void set_bitarray(bitarray *a, int pos) {
    a->array[pos] = 1;
}

/* Set position pos in the bitarray to 0 */
void reset_bitarray(bitarray *a, int pos) {
    a->array[pos] = 0;
}

/* Get the value at position pos in the bitarray */
int get_bitarray(bitarray *a, int pos) {
    return a->array[pos];
}

/* Set all positions in the bitarray to 0 */
void clear_bitarray(bitarray *a) {
    a->array = (unsigned char *) calloc(a->size, sizeof(unsigned char));
}
