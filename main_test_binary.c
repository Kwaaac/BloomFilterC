#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filter.h"
#include <string.h>
#include "tree_word.h"

#define MAX_READ 100

int main(int argc, char *argv[]) {
    int k, m, i, maybe = 0, no = 0;
    char *file_in, *file_out;
    size_t word_length;
    FILE *f;
    node *node = NULL;
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

    f = fopen(file_in, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_in);
        return 0;
    }

    while (fgets(str, MAX_READ, f) != NULL) {
        word_length = strlen(str);
        if (word_length == 4 || word_length == 5) {
            node = insert_bst(node, str);
        }
    }

    fclose(f);

    f = fopen(file_in, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file_in);
        return 0;
    }

    freopen(file_out, "w+", stdout);

    while (fgets(str, MAX_READ, f) != NULL) {
        if (find_bst(node, str)) {
            printf("%s: \t yes\n", str);
            maybe++;
        } else {
            printf("%s: \t non\n", str);
            no++;
        }
    }

    printf("There is %d yes and %d no", maybe, no);

    fclose(f);
    
    free_tree(node);

    return 0;
}
