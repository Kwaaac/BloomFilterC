#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitarray.h"
#include "filter.h"

int *_tst_bitarray;
int _tst_m;

typedef struct __tst_link {
    char *str;
    struct __tst_link *next;
} _tst_link;

_tst_link *_tst_filter;

void _tst_create_bitarray(int _m) {
    _tst_m = _m;
    _tst_bitarray = malloc(_tst_m * sizeof(int));
    memset(_tst_bitarray, 0, _tst_m * sizeof(int));;
}

void _tst_free_bitarray() {
    free(_tst_bitarray);
}

void _tst_set_bitarray(int pos) {
    _tst_bitarray[pos] = 1;
}

void _tst_reset_bitarray(int pos) {
    _tst_bitarray[pos] = 0;
}

int _tst_get_bitarray(int pos) {
    return _tst_bitarray[pos];
}

void _tst_clear_bitarray() {
    memset(_tst_bitarray, 0, _tst_m * sizeof(int));
}

void _tst_create_filter() {
    _tst_filter = NULL;
}

void _tst_free_filter() {
    while (_tst_filter) {
        free(_tst_filter->str);
        _tst_link *tmp = _tst_filter;
        _tst_filter = _tst_filter->next;
        free(tmp);
    }
}

void _tst_add_filter(char *str) {
    _tst_link *new_link = malloc(sizeof(_tst_link));
    new_link->str = malloc(strlen(str) + 1);
    strcpy(new_link->str, str);
    new_link->next = _tst_filter;
    _tst_filter = new_link;
}

int _tst_is_member_filter(char *str) {
    _tst_link *ptr = _tst_filter;
    while (!ptr) {
        if (!strcmp(ptr->str, str))
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

int _compare_bitarray(bitarray *ba, int m) {
    int i;
    for (i = 0; i < m; i++)
        if (_tst_get_bitarray(i) != get_bitarray(ba, i)) return 0;
    return 1;
}

int _nsizes = 15;
int _sizes[] = {1, 8, 15, 16, 17, 31, 32, 33, 63, 64, 65, 333, 1024, 16384, 5000000};

int verify_create_bitarray() {
    int res = 1;
    int size;
    for (size = 0; size < _nsizes; size++) {
        _tst_create_bitarray(_sizes[size]);
        bitarray *ba = create_bitarray(_sizes[size]);
        int comp = _compare_bitarray(ba, _sizes[size]);
        if (comp != 1) {
            if (res == 1) printf("\033[1mcreate_bitarray FAILED\033[0m (bitarray not 0) for sizes: ");
            printf("%d ", _sizes[size]);
            res = 0;
        }
        _tst_free_bitarray();
        free_bitarray(ba);
    }
    if (res == 0) printf("\n");
    return res;
}

int verify_set_bitarray() {
    int res = 1;
    int size;
    for (size = 0; size < _nsizes; size++) {
        _tst_create_bitarray(_sizes[size]);
        bitarray *ba = create_bitarray(_sizes[size]);
        int j;
        for (j = 0; j < _sizes[size] / 3; j++) {
            int pos = rand() % _sizes[size];
            _tst_set_bitarray(pos);
            set_bitarray(ba, pos);
        }
        int comp = _compare_bitarray(ba, _sizes[size]);
        if (comp != 1) {
            if (res == 1) printf("\033[1mset_bitarray FAILED\033[0m for sizes: ");
            printf("%d ", _sizes[size]);
            res = 0;
        }
        _tst_free_bitarray();
        free_bitarray(ba);
    }
    if (res == 0) printf("\n");
    return res;
}

int verify_reset_bitarray() {
    int res = 1;
    int size;
    for (size = 0; size < _nsizes; size++) {
        _tst_create_bitarray(_sizes[size]);
        bitarray *ba = create_bitarray(_sizes[size]);
        int j;
        for (j = 0; j < _sizes[size]; j++) {
            _tst_set_bitarray(j);
            set_bitarray(ba, j);
        }
        for (j = 0; j < _sizes[size] / 3; j++) {
            int pos = rand() % _sizes[size];
            _tst_reset_bitarray(pos);
            reset_bitarray(ba, pos);
        }
        int comp = _compare_bitarray(ba, _sizes[size]);
        if (comp != 1) {
            if (res == 1) printf("\033[1mreset_bitarray FAILED\033[0m for sizes: ");
            printf("%d ", _sizes[size]);
            res = 0;
        }
        _tst_free_bitarray();
        free_bitarray(ba);
    }
    if (res == 0) printf("\n");
    return res;
}

int verify_clear_bitarray() {
    int res = 1;
    int size;
    for (size = 0; size < _nsizes; size++) {
        _tst_create_bitarray(_sizes[size]);
        bitarray *ba = create_bitarray(_sizes[size]);
        int j;
        for (j = 0; j < _sizes[size]; j++) {
            _tst_set_bitarray(j);
            set_bitarray(ba, j);
        }
        _tst_clear_bitarray();
        clear_bitarray(ba);
        int comp = _compare_bitarray(ba, _sizes[size]);
        if (comp != 1) {
            if (res == 1) printf("\033[1mclear_bitarray FAILED\033[0m (bitarray not 0) for sizes: ");
            printf("%d ", _sizes[size]);
            res = 0;
        }
        _tst_free_bitarray();
        free_bitarray(ba);
    }
    if (res == 0) printf("\n");
    return res;
}

int _is_empty_filter(filter *f) {
    char a[4];
    a[3] = '\0';
    for (a[0] = 1; a[0] < 127; a[0]++)
        for (a[1] = 1; a[1] < 127; a[1]++)
            for (a[2] = 1; a[2] < 127; a[2]++)
                if (is_member_filter(f, a) == 1) {
                    return 0;
                }
    return 1;
}

int _nfsizes = 4;
int _fsizes[] = {333, 1024, 16384, 5000000};

int verify_create_filter() {
    int res = 1;
    int size;
    for (size = 0; size < _nfsizes; size++) {
        int k = 3 + rand() % 10;
        _tst_create_filter();
        filter *f = create_filter(_fsizes[size], k);
        int comp = _is_empty_filter(f);
        if (comp != 1) {
            if (res == 1) printf("\033[1mcreate_filter FAILED\033[0m (filter not empty) for (size, k): ");
            printf("(%d, %d) ", _fsizes[size], k);
            res = 0;
        }
        _tst_free_filter();
        free_filter(f);
    }
    if (res == 0) printf("\n");
    return res;
}

int verify_add_filter() {
    int nwords = 20;
    char *wordlist[] =
            {"baby", "back", "bad", "bag", "ball",
             "bank", "bar", "base", "be", "beat",
             "camera", "campaign", "can", "candidate", "capital",
             "car", "card", "care", "career", "carry"};
    int res = 1;
    int size;
    for (size = 0; size < _nfsizes; size++) {
        int k = 3 + rand() % 10;
        filter *f = create_filter(_fsizes[size], k);
        int j;
        for (j = 0; j < nwords; j++) {
            add_filter(f, wordlist[j]);
        }
        for (j = 0; j < nwords; j++) {
            if (is_member_filter(f, wordlist[j]) == 0) {
                if (res == 1) printf("\033[1madd_filter FAILED\033[0m failed for (size, k, missing word): ");
                printf("(%d, %d, %s) ", _fsizes[size], k, wordlist[j]);
                res = 0;
            }
        }
        free_filter(f);
    }
    if (res == 0) printf("\n");
    return res;
}

void display_begin(char *name) {
    printf("\n*** Verify function %s\n", name);
}

void display_end(char *name, int res) {
    if (res == 1)
        printf("*** %s PASSED\n", name);
    else
        printf("*** %s \033[1mFAILED\033[0m\n", name);
}

int main() {

    srand(time(NULL));

    int res;
    int score = 0;

    /* bitarray */

    display_begin("create_bitarray");
    res = verify_create_bitarray();
    display_end("create_bitarray", res);
    score += 1 - res;

    display_begin("set_bitarray");
    res = verify_set_bitarray();
    display_end("set_bitarray", res);
    score += 1 - res;

    display_begin("reset_bitarray");
    res = verify_reset_bitarray();
    display_end("reset_bitarray", res);
    score += 1 - res;

    display_begin("clear_bitarray");
    res = verify_clear_bitarray();
    display_end("clear_bitarray", res);
    score += 1 - res;

    /* filter */

    display_begin("create_filter");
    res = verify_create_filter();
    display_end("create_filter", res);
    score += 1 - res;

    display_begin("add_filter");
    res = verify_add_filter();
    display_end("add_filter", res);
    score += 1 - res;

    if (score == 0)
        printf("\n\033[1mAll tests PASSED\033[0m\n");
    else
        printf("\n\033[1m%d tests FAILED\033[0m\n", score);

    return 0;
}
