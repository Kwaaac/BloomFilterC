#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "filter.h"

int main(int argc, char *argv[]) {
    /* Test tirage k poids entre 0 et 255 */
    /*int i;
    srand(time(NULL));

    for (i = 0; i < 1000; i++) {
        int value = (rand() % 254) + 2;
        if (value == 0 || value == 1 || value == 2 || value == 256 || value == 255 || value == 254 || value == 253) {
            printf("Poids = %d\n", value);
        }
    }*/
    /* Fin test */

    int i;
    filter *f = create_filter(64, 5);
    for (i = 0; i < f->k; i++) {
        printf("Poids %d du filtre = %d\n", i, f->weigth[i]);
    }

    return 0;
}
