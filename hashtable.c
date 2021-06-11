#include "hashtable.h"

unsigned hash_hashtable(const char *elt, int M) {
    int i;
    unsigned h;
    h = 0;
    for (i = 0; elt[i] != '\0'; i++) {
        h = (31 * h + elt[i]) % M;
    }
    return h;
}

/**
 * Create a link representing 1 occurence of the string 'word'.
 * The string is copied and must be freed when the link is freed.
 */
link *create_link(char word[]) {
    link *lnk = malloc(sizeof(link));
    lnk->word = malloc(strlen(word) + 1);
    assert(word != NULL);
    strcpy(lnk->word, word);
    lnk->count = 1;
    lnk->next = NULL;

    return lnk;
}

void free_link(link *lnk) {
    free(lnk->word);
    free(lnk);
}

void free_hash_table(hashtable *hash_table) {
    int i;
    for (i = 0; i < hash_table->M; i++) {
        free_list(hash_table->bucket[i]);
    }
    free(hash_table->bucket);
    free(hash_table);
}

void add_occ_table(hashtable *tab, char word[]) {
    link *lst;
    unsigned hash_index = hash_hashtable(word, tab->M);
    lst = find_list(tab->bucket[hash_index], word);
    if (lst == NULL)
        tab->bucket[hash_index] = insert_first_list(tab->bucket[hash_index], word);
    else
        add_occurrence(lst);
    tab->size++;
}

/**
 * Find the word in the hashtable
 *
 * @param tab the hastable
 * @param word the word
 * @return 1 if the word is in the hashtable, 0 otherwise
 */
int find_table(hashtable *tab, char word[]) {
    unsigned hash_index = hash_hashtable(word, tab->M);
    return find_list(tab->bucket[hash_index], word) != NULL;
}

void free_list(link *lst) {
    while (lst) {
        link *tmp = lst;
        lst = lst->next;
        free_link(tmp);
    }

    free(lst);
}

link *find_list(link *lst, char word[]) {
    link *ptr = lst;
    while (ptr != NULL && strcmp(ptr->word, word) != 0)
        ptr = ptr->next;
    return ptr;
}


link *insert_first_list(link *lst, char word[]) {
    link *tmp = create_link(word);
    tmp->next = lst;
    return tmp;
}

void display_list(link *lst) {
    link *ptr = lst;
    while (ptr) {
        printf("\"%s\" apparrait %d fois \n", ptr->word, ptr->count);

        ptr = ptr->next;
    }
}

hashtable *create_table(int M) {
    int i;
    hashtable *hash_table = (hashtable *) malloc(sizeof(hashtable));
    assert(hash_table != NULL);
    hash_table->bucket = (link **) malloc(M * sizeof(link *));
    assert(hash_table->bucket != NULL);
    for (i = 0; i < M; i++) {
        hash_table->bucket[i] = NULL;
    }
    hash_table->M = M;
    hash_table->size = 0;

    return hash_table;
}

link *add_occurrence(link *lnk) {
    lnk->count++;
    return lnk;
}
