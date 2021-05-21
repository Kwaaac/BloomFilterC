#include <math.h>
#include "filter.h"
#include <time.h>

#define SECONDARY_STRUCT 0

filter *create_filter(int m, int k) {
    int i;

    filter *new_filter = (filter *) malloc(sizeof(filter));
    assert(new_filter != NULL);

    new_filter->array = create_bitarray(m);
    new_filter->k = k;
    new_filter->weigth = (unsigned int *) calloc(k, sizeof(unsigned int));
    if (SECONDARY_STRUCT == 1) {
        new_filter->table = create_table(m);
    }
    assert(new_filter->weigth != NULL);

    /* Tirer au hasard k poids différents entre 2 et 255 et placer ces poids dans un tableau */
    srand(time(NULL)); /*TODO: à déplacer un jour dans le main par peur de perdre l'aléatoire*/
    for (i = 0; i < k; i++) {
        new_filter->weigth[i] = (rand() % 254) + 2;
    }
    /* Fin tirage de k poids */

    return new_filter;
}

/* Compute k hash values for the string str and place them in the
array hashes. */
void hash(filter *f, char *str, unsigned int hashes[]) {
    int i, j, size_str;
    size_str = 0;
    for (i = 0; str[i] != '\0'; i++) {
        size_str++;
    }

    for (i = 0; i < f->k; i++) {
        unsigned int h;
        h = 0;
        for (j = 0; j < size_str; j++) {
            h += str[j] * pow(f->weigth[i], (size_str - (j + 1)));
        }
        hashes[i] = h % f->array->size;
    }
}

void free_filter(filter *f) {
    free_bitarray(f->array);
    free(f->weigth);
    if (SECONDARY_STRUCT == 1) {
        free_hash_table(f->table);
    }
    free(f);
}

void add_filter(filter *f, char *str) {
    int i, size = f->k;
    unsigned int *hashes = (unsigned int *) calloc(size, sizeof(unsigned int));
    hash(f, str, hashes);

    for (i = 0; i < size; i++) {
        set_bitarray(f->array, hashes[i]);
    }

    /* Secondary structure */
    if (SECONDARY_STRUCT == 1) {
        add_occ_table(f->table, str);
    }

    free(hashes);
}

int is_member_filter(filter *f, char *str) {
    int i, size = f->k;
    unsigned int *hashes = (unsigned int *) calloc(size, sizeof(unsigned int));
    hash(f, str, hashes);

    for (i = 0; i < size; i++) {
        if (get_bitarray(f->array, hashes[i]) == 0) {
            return 0;
        }
    }

    /* TODO: Vérifier si c'est un faut positif */
    if (SECONDARY_STRUCT == 1) {
        return find_table(f->table, str);
    }

    free(hashes);
    return 1;
}
