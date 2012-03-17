#include <stdlib.h>
#include <string.h>
#include "dict.h"

typedef struct DictEntry {
    char *key;
    void *val;
} DictEntry;

void *make_dict(void *parent) {
    Dict *r = malloc(sizeof(Dict));
    r->list = make_list();
    r->parent = parent;
    return r;
}

void *dict_get(Dict *dict, char *key) {
    for (; dict; dict = dict->parent) {
        for (Iter *i = list_iter(dict->list); !iter_end(i);) {
            DictEntry *e = iter_next(i);
            if (!strcmp(key, e->key))
                return e->val;
        }
    }
    return NULL;
}

void dict_put(Dict *dict, char *key, void *val) {
    DictEntry *e = malloc(sizeof(DictEntry));
    e->key = key;
    e->val = val;
    list_push(dict->list, e);
}

void *dict_parent(Dict *dict) {
    return dict->parent;
}