#ifndef TREE_H
#define TREE_H

#include <string.h>

typedef struct _node {
    char *word;                /* word stored : a string    */
    struct _node *left;      /* pointer to the left child   */
    struct _node *right;     /* pointer to the right child  */
} node;

/*
 * Allocate memory for a new node.
 */
node *create_node(char *word);

void free_tree(node *t);

void display_path_prefix(node *t);

void display_path_infix(node *t);

void display_path_suffix(node *t);

node *scan_tree();

int count_nodes(node *t);

int count_leaves(node *t);

int count_only_children(node *t);

int height(node *t);


/*============ TP 8 ============*/

node *find_bst(node *t, char *word);

node *insert_bst(node *t, char *word);

node *remove_bst(node *t, char *word);

void display_between(node *t, char *word1, char *word2);

#endif /* TREE_H */
