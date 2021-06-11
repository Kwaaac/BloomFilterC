#include <stdio.h>
#include <stdlib.h>

#include "filter.h"
#include "hashtable.h"

#define MAX_READ 100

int main(int argc, char *argv[]) {
    int k, m, i, maybe = 0, yes = 0, no = 0, false_positive = 0;
    float n;
    char *file_in, *file_out;
    FILE *f, *f_out;
    size_t word_length;
    filter *bloom;
    hashtable *hash_table;
    char str[MAX_READ];

    for (i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-fin") == 0) {
            file_in = argv[i + 1];
        } else if (strcmp(argv[i], "-fout") == 0) {
            file_out = argv[i + 1];
        } else if (strcmp(argv[i], "-k") == 0) {
            k = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            m = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-n") == 0) {
            n = atof(argv[i + 1]);
        }
    }

    bloom = create_filter(m, k);
    hash_table = create_table(m);

    f = fopen(file_in, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_in);
        return 0;
    }

    while (fgets(str, MAX_READ, f) != NULL) {
        word_length = strlen(str);
        if (word_length == 4 || word_length == 5) {
            add_filter(bloom, str);
            add_occ_table(hash_table, str);
        }
    }

    fclose(f);

    f = fopen(file_in, "r");
    f_out = fopen(file_out, "w+");

    if (f == NULL || f_out == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s ou %s\n", file_in, file_out);
        return 0;
    }

    while (fgets(str, MAX_READ, f) != NULL) {

        if (is_member_filter(bloom, str)) {
            if (find_table(hash_table, str)) {
                fprintf(f_out, "%s: \t yes\n", str);
                yes++;
            } else {
                fprintf(f_out, "%s: \t False positive\n", str);
                false_positive++;
            }

            maybe++;

        } else {
            fprintf(f_out, "%s: \t non\n", str);
            no++;
        }
    }

    printf("There is %d maybes and %d no, and finally %d false positives, so there is a %f percentage of false positive\n",
           maybe, no, false_positive, (float) (false_positive * 100.0) / n);

    fclose(f_out);
    fclose(f);

    free_filter(bloom);
    free_hash_table(hash_table);

    return 0;
}

