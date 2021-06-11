#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filter.h"
#include "hashtable.h"

#define MAX_READ 100

int main(int argc, char *argv[]) {
    int k, m, i, n, flag, maybe = 0, yes = 0, no = 0, false_positive = 0;
    char *file_in, *file_test, *file_out;
    FILE *f;
    filter *bloom;
    hashtable *hash_table;
    unsigned int *hashes;
    char str[MAX_READ];

    for (i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-fin") == 0) {
            file_in = argv[i + 1];
        } else if (strcmp(argv[i], "-ftest") == 0) {
            file_test = argv[i + 1];
        } else if (strcmp(argv[i], "-fout") == 0) {
            file_out = argv[i + 1];
        } else if (strcmp(argv[i], "-k") == 0) {
            k = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            m = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-n") == 0) {
            n = atoi(argv[i + 1]);
        }
    }

    bloom = create_filter(m, k);
    hash_table = create_table(m);

    f = fopen(file_in, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_in);
        return 0;
    }

    hashes = (unsigned int *) malloc(sizeof(unsigned int) * k);
    int bob = 0;
    while (fgets(str, MAX_READ, f) != NULL) {
        for (i = 0; i < bloom->k; i++) {
            add_filter(bloom, str);
        }
        add_occ_table(hash_table, str);
        bob++;
    }



    /* test.txt sur les 1000 passwords */
    fclose(f);

    f = fopen(file_test, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_out);
        return 0;
    }

    freopen(file_out, "w+", stdout);

    while (fgets(str, MAX_READ, f) != NULL) {

        if (is_member_filter(bloom, str)) {
            if (find_table(hash_table, str)) {
                printf("%s: \t oui\n", str);
                yes++;
            } else {
                printf("%s: \t Faux positif\n", str);
                false_positive++;
            }

            maybe++;

        } else {
            printf("%s: \t non\n", str);
            no++;
        }
    }

    printf("There is %d maybes and %d no, and finally %d false positives, so there is a %d percentage of false positive",
           maybe, no, false_positive, (false_positive * 100) / 1000);

    fclose(f);

    free_filter(bloom);
    free_hash_table(hash_table);

    return 0;
}

