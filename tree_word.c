#include "tree_word.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "read.h"

int equal(char *s1, char *s2) {
    return strcmp(s1, s2) == 0;
}

int less(char *s1, char *s2) {
    return strcmp(s1, s2) < 0;
}

node *create_node(char *word) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->word = (char *) malloc((strlen(word) + 1) * sizeof(char));
    strcpy(new_node->word, word);
    return new_node;
}

void free_tree(node *t) {
    if (t->left != NULL) {
        free_tree(t->left);
    }
    if (t->right != NULL) {
        free_tree(t->right);
    }
    free(t->word);
    free(t);
}


void display_path_prefix(node *t) {
    if (t != NULL) {
        printf("%s ", t->word);
        display_path_prefix(t->left);
        display_path_prefix(t->right);
    }
}

void display_path_infix(node *t) {
    if (t != NULL) {
        display_path_infix(t->left);
        printf("%s ", t->word);
        display_path_infix(t->right);
    }
}

void display_path_suffix(node *t) {
    if (t != NULL) {
        display_path_suffix(t->left);
        display_path_suffix(t->right);
        printf("%s ", t->word);
    }
}

int count_nodes(node *t) {
    if (t == NULL) {
        return 0;
    }

    return 1 + count_nodes(t->left) + count_nodes(t->right);
}


int count_leaves(node *t) {
    if (t == NULL) {
        return 0;
    }

    if (t->right == NULL && t->left == NULL) {
        return 1;
    }

    return count_leaves(t->left) + count_leaves(t->right);
}

int count_number_of_children(node *t) {
    int res = 0;
    if (t->left != NULL) res++;
    if (t->right != NULL) res++;
    return res;
}

int count_only_children(node *t) {
    if (t == NULL) {
        return 0;
    }

    if (count_number_of_children(t) == 1) {
        return 1 + count_only_children(t->left) + count_only_children(t->right);
    }

    return count_only_children(t->left) + count_only_children(t->right);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int height(node *t) {
    if (t == NULL) {
        return -1;
    }

    return max(height(t->left), height(t->right)) + 1;
}

/*============ TP 8 ============*/
node *find_bst(node *t, char *word) {
    if (t == NULL || equal(t->word, word)) {
        return t;
    }

    if (less(t->word, word)) {
        return find_bst(t->right, word);
    }

    return find_bst(t->left, word);

    /* version rigolote mais franchement illisible
    return less(t->word, word) ? find_bst(t->right, word) : find_bst(t->left, word);
    */
}

node *insert_bst(node *t, char *word) {
    if (t == NULL) {
        t = create_node(word);
    }

    if (equal(t->word, word)) {
        return t;
    } else if (less(t->word, word)) {
        t->right = insert_bst(t->right, word);
    } else {
        t->left = insert_bst(t->left, word);
    }

    return t;
}

node *extract_min_bst(node *t, node **min) {
    if (t->left != NULL) {
        t->left = extract_min_bst(t->left, min);
    } else {
        *min = t;
        t = t->right;
    }
    return t;
}

node *remove_bst(node *t, char *word) {
    if (t == NULL)
        return NULL;
    else if (less(word, t->word))
        t->left = remove_bst(t->left, word);
    else if (less(t->word, word))
        t->right = remove_bst(t->right, word);
    else {

        /*
         *      t
         *     / \
         *  left right
         */

        node *left = t->left;
        node *right = t->right;
        free(t);

        if (left == NULL)
            return right;
        if (right == NULL)
            return left;

        /* il y a deux fils, left != NULL, right != NULL */

        /*
         *      t                   succ
         *     / \                  /  \
         *  left right            left right
         *       /         =>
         *      ...
         *     /
         *    succ
         */

        node *succ;
        right = extract_min_bst(right, &succ);
        succ->left = left;
        succ->right = right;
        t = succ; /* ou return succ */
    }

    return t;
}

void display_between(node *t, char *word1, char *word2) {
    if (t != NULL) {
        display_between(t->left, word1, word2);
        if (less(word1, t->word) && less(t->word, word2)) {
            printf("%s ", t->word);
        }

        display_between(t->right, word1, word2);
    }
}
