#ifndef BLOOMFILTERC_HASHTABLE_H
#define BLOOMFILTERC_HASHTABLE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct _link {
    char *word;
    int count;
    struct _link *next;
} link;

typedef struct _hashtable {
    link **bucket;
    int M; /* nombre de seaux */
    int size; /* nombre de mots dans la table */
} hashtable;

hashtable* create_table(int M);

void free_hash_table(hashtable* hash_table);

void add_occ_table(hashtable *tab, char word[], int pos);

void free_list(link *lst);

link *find_list(link *lst, char word[]);

link *insert_first_list(link *lst, char word[], int pos);

void display_list(link *lst);

link *add_occurrence(link *lnk, int pos);

#endif /* BLOOMFILTERC_HASHTABLE_H */
