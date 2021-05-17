#include <math.h>
#include <z3_api.h>
#include "filter.h"

filter *create_filter(int m, int k) {
    return NULL;
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
    /*str[0] ∗ (poids[i]^t-1) + str[1] ∗ (poids[i])^t−2 + ... + str[t − 2] ∗ (poids[i])^1 + str[t − 1]*/
}
