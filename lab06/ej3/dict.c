#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool inv;
    if (d == NULL || (d->left == NULL && d->right == NULL)) { 
        inv = true; 
    } else if (d->left == NULL) { 
        inv = string_less(d->key, d->right->key) && invrep(d->right); 
    } else if (d->right == NULL) { 
        inv = string_less(d->left->key, d->key) && invrep(d->left); 
    } else { 
        inv = string_less(d->key, d->right->key) && invrep(d->right) && string_less(d->left->key, d->key) && invrep(d->left); 
    }
    return inv;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict == NULL) {
        dict = calloc(1, sizeof(struct _node_t));
        assert(dict != NULL);
        dict->left = NULL;
        dict->right = NULL;
        dict->key = word;
        dict->value = def;
    } else if (string_eq(word, dict->key)) {
        dict->value = def;
    } else if (string_less(word, dict->key)) {
        dict->left = dict_add(dict->left, word, def);
    } else if (string_less(dict->key, word)) {
        dict->right = dict_add(dict->right, word, def);
    }
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def = NULL;
    if (dict == NULL) {
        def = NULL;
    } else if (string_eq(dict->key, word)) {
        def = dict->value;
    } else if (string_less(word, dict->key)) {
        def = dict_search(dict->left, word);
    } else if (string_less(dict->key, word)) {
        def = dict_search(dict->right, word);
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    if (dict == NULL) {
        exists = false;
    } else if (string_eq(dict->key, word)) {
        exists = true;
    } else if (string_less(word, dict->key)) {
        exists =  dict_exists(dict->left, word);
    } else if (string_less(dict->key, word)) {
        exists = dict_exists(dict->right, word);
    }
    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = 0u;
    if (dict != NULL) {
        length = dict_length(dict->left) + dict_length(dict->right) + 1u;
    }
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if (dict == NULL) {
        return NULL;
    }
    if (string_less(word, dict->key)) {
        dict->left = dict_remove(dict->left, word);
    } else if (string_less(dict->key, word)) {
        dict->right = dict_remove(dict->right, word);
    } else {  // dict->key == word
        if (dict->left == NULL && dict->right == NULL) {
            key_destroy(dict->key);
            value_destroy(dict->value);
            free(dict);
            dict = NULL;
        } else if (dict->left == NULL) {
            dict_t temp = dict->right;
            key_destroy(dict->key);
            value_destroy(dict->value);
            free(dict);
            dict = temp;
        } else if (dict->right == NULL) {
            dict_t temp = dict->left;
            key_destroy(dict->key);
            value_destroy(dict->value);
            free(dict);
            dict = temp;
        } else {
            dict_t temp = dict->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            dict->key = temp->key;
            dict->value = temp->value;
            temp->key = NULL; // Evitar que se libere dos veces
            temp->value = NULL; // Evitar que se libere dos veces
            dict->right = dict_remove(dict->right, dict->key);
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if (dict == NULL) {
        return dict;
    }
    if (dict->left != NULL) {
        dict->left = dict_remove_all(dict->left);
    }
    if (dict->right != NULL) {
        dict->right = dict_remove_all(dict->right);
    }
    dict->key = key_destroy(dict->key);
    dict->value = value_destroy(dict->value);
    free(dict);
    dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL)  {
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->left, file);
        dict_dump(dict->right, file);   
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    assert(dict == NULL);
    return dict;
}