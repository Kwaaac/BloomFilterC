#include <math.h>
#include "filter.h"
#include <time.h>

#define SECONDARY_STRUCT 0

filter *create_filter(int m, int k) {
    int i, j, t;

    filter *new_filter = (filter *) malloc(sizeof(filter));
    assert(new_filter != NULL);

    new_filter->array = create_bitarray(m);

    if (k < 2) {
        k = 2;
    }
    else if (k > 255) {
        k = 255;
    }
    new_filter->k = k;
    new_filter->weigth = (unsigned int *) calloc(k, sizeof(unsigned int));
    assert(new_filter->weigth != NULL);

    /* Tirer au hasard k poids différents entre 2 et 255 et placer ces poids dans un tableau */

    /* Ancien tirage des poids */
    /*srand(time(NULL)); TODO: à déplacer un jour dans le main par peur de perdre l'aléatoire
    for (i = 0; i < k; i++) {
        new_filter->weigth[i] = (rand() % 254) + 2;
    }*/
    /* Fin ancien tirage des poids */

    /* Nouveau tirage des poids */
    int array_size = 254;
    int array[array_size];

    /* Filling the values array */
    for (i = 0; i < array_size; i++) {
        array[i] = i + 2;
    }

    /* Shuffling the values array */
    /*srand(time(NULL));
    for (i = 0; i < array_size; i++) {
        j = (rand() % 254);
        t = array[j];
        array[j] = array[i];
        array[i] = t;
    }*/

    /* Filling the weigth array with the k firsts int from the values array */
    for (i = 0; i < k; i++) {
        new_filter->weigth[i] = array[i];
    }

    /* Printing the two arrays */
    /*printf("Values array :\n[");
    for (i = 0; i < array_size; i++) {
        printf("%d", array[i]);
        if (i != array_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Weigth array:\n[");
    for (i = 0; i < k; i++) {
        printf("%d", new_filter->weigth[i]);
        if (i != k - 1) {
            printf(", ");
        }
    }
    printf("]");*/
    /* Fin nouveau tirage des poids */

    /* Fin tirage de k poids */

    /* Allocation du tableau de hashes (conseil du professeur) */
    new_filter->hashes = (unsigned int *) calloc(new_filter->k, sizeof(unsigned int));
    /* Fin allocation du tableau de hashes (conseil du professeur) */

    if (SECONDARY_STRUCT == 1) {
        new_filter->table = create_table(m);
    }

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
        /* Actual hash method */
        unsigned int h;
        h = 0;
        for (j = 0; j < size_str; j++) {
            h += str[j] * pow(f->weigth[i], (size_str - (j + 1)));
        }

        hashes[i] = h % f->array->size;

        /*printf("Actual %d => %d, ", i, hashes[i]);*/
        /* End actual hash method */

        /* Test new hash method */
        /*unsigned int h;
        h = 0;
        for (j = 0; j < size_str; j++) {
            h = str[j] * h + f->weigth[i];
        }

        hashes[i] = h % f->array->size;*/

        /*printf("New %d => %d, ", i, hashes[i]);*/
        /* End test new hash method */
    }
    /*printf("\n");*/
}

void free_filter(filter *f) {
    free_bitarray(f->array);
    free(f->weigth);
    free(f->hashes);
    if (SECONDARY_STRUCT == 1) {
        free_hash_table(f->table);
    }
    free(f);
}

void add_filter(filter *f, char *str) {
    int i, size = f->k;
    hash(f, str, f->hashes);

    for (i = 0; i < size; i++) {
        set_bitarray(f->array, f->hashes[i]);
    }

    /* Secondary structure */
    if (SECONDARY_STRUCT == 1) {
        add_occ_table(f->table, str);
    }

    /* Reset the hashes array with zeros */
    for (i = 0; i < size; i++) {
        f->hashes[i] = 0;
    }
}

int is_member_filter(filter *f, char *str) {
    int i, size = f->k;
    hash(f, str, f->hashes);

    for (i = 0; i < size; i++) {
        if (get_bitarray(f->array, f->hashes[i]) == 0) {
            /* Reset the hashes array with zeros */
            for (i = 0; i < size; i++) {
                f->hashes[i] = 0;
            }
            return 0;
        }
    }

    /* TODO: Vérifier si c'est un faut positif */
    if (SECONDARY_STRUCT == 1) {
        free(f->hashes);
        return find_table(f->table, str);
    }

    /* Reset the hashes array with zeros */
    for (i = 0; i < size; i++) {
        f->hashes[i] = 0;
    }
    return 1;
}
