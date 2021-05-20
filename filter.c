
#include <stdlib.h>
/*#include <math.h>*/
#include <time.h>

#include "filter.h"

/* Fonction pour faire une élévation à la puissance */
long pow(int weigth, int exp) {
    int i;
    long result = weigth;
    for(i = 0; i < exp; i++) {
        result = result * weigth;
    }
    return result;
}
/* Fin fonction élévation à la puissance */

filter *create_filter(int m, int k) {
    int i;

    filter *new_filter = (filter *)malloc(sizeof(filter));
    assert(new_filter != NULL);

    new_filter->array = create_bitarray(m);
    new_filter->k = k;
    new_filter->weigth = (unsigned int *)calloc(k, sizeof(unsigned int)); /* Vérifier si c'est bien k fois */
    assert(new_filter->weigth != NULL);

    /* Tirer au hasard k poids différents entre 2 et 255 et placer ces poids dans un tableau */
    srand(time(NULL));
    for (i = 0; i < k; i++) {
        new_filter->weigth[i] = (rand() % 254) + 2;
    }
    /* Fin tirage de k poids */

    return new_filter;
}

void free_filter(filter *f) {
    free_bitarray(f->array);
    free(f->weigth);
    free_filter(f);
}

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
        f->weigth[i] = h;
    }
}

void add_filter(filter *f, char *str) {
    /* A FINIR */
}

int is_member_filter(filter *f, char *str) {
    return 0;   /* A FINIR */
}