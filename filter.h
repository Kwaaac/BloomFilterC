#ifndef BLOOMFILTERC_FILTER_H
#define BLOOMFILTERC_FILTER_H

#include "bitarray.h"
#include "hashtable.h"

typedef struct _filter {
    bitarray *array;
    int k;
    unsigned int *weigth;

    /* Tableau de hashes (conseil du professeur)
     * Interet : Eviter d'allouer le tableau à chaque fois*/
    unsigned int *hashes;
} filter;

/* Return a pointer to an empty filter with parameters m and k */
filter *create_filter(int m, int k);

/* Free the memory associated with the filter */
void free_filter(filter *f);

/* Compute k hash values for the string str and place them in the
array hashes. */
void hash(filter *f, char *str, unsigned int hashes[]);

/* Add the key str to the filter */
void add_filter(filter *f, char *str);

/* Check if the key str is in the filter, 0 means no, 1 means maybe */
int is_member_filter(filter *f, char *str);

#endif /* BLOOMFILTERC_FILTER_H */
