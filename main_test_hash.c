#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filter.h"
#include <string.h>

#define MAX_READ 100

int main(int argc, char *argv[]) {
    int k, m, i, flag, maybe = 0, no = 0;
    char *file_in, *file_out;
    size_t word_length;
    FILE *f;
    filter *bloom;
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
        }
    }

    bloom = create_filter(m, k);

    f = fopen(file_in, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_in);
        return 0;
    }

    unsigned int *hashes = (unsigned int *) malloc(sizeof(unsigned int) * k);

    while (fgets(str, MAX_READ, f) != NULL) {
        word_length = strlen(str);
        if (word_length == 4 || word_length == 5) {
            for (i = 0; i < bloom->k; i++) {
                add_filter(bloom, str);
            }
        }
    }

    /* test.txt sur les 1000 passwords */
    fclose(f);

    f = fopen(file_in, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_in);
        return 0;
    }

    freopen(file_out, "w+", stdout);

    while (fgets(str, MAX_READ, f) != NULL) {
        if (is_member_filter(bloom, str)) {
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
