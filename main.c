#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filter.h"

#define MAX_READ 100

int main(int argc, char *argv[]) {
    int k, m, i, flag, maybe = 0, no = 0;
    char *filename;
    FILE *f;
    filter *bloom;
    char str[MAX_READ];

    for (i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
        } else if (strcmp(argv[i], "-k") == 0) {
            k = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            m = atoi(argv[i + 1]);
        }
    }

    bloom = create_filter(m, k);

    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", filename);
        return 0;
    }

    unsigned int* hashes = (unsigned int *) malloc(sizeof(unsigned int) * k);

    while (fgets(str, MAX_READ, f) != NULL) {
        for (i = 0; i < bloom->k; i++) {
            add_filter(bloom, str);
        }
    }

    /* test.txt sur les 1000 passwords */
    fclose(f);

    f = fopen("passwords/1000password.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", "passwords/1000password.txt");
        return 0;
    }

    freopen("passwords/results.txt", "w+", stdout);

    while (fgets(str, MAX_READ, f) != NULL) {
        hash(bloom, str, hashes);

        flag = 1;

        for (i = 0; i < bloom->k; i++) {
            if (is_member_filter(bloom, str) == 0) {
                flag = 0;
            }
        }

        if (flag) {
            printf("%s: \t peut-être\n", str);
            maybe++;
        } else {
            printf("%s: \t non\n", str);
            no++;
        }

    }

    printf("There is %d maybe and %d no", maybe, no);

    fclose(f);

    free_filter(bloom);

    return 0;
}
