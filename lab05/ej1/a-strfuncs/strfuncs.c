#include <stdlib.h>
#include <stdbool.h>

#include "strfuncs.h"

size_t string_length(const char *str) {
    size_t len = 0;
    if (str != NULL) {
        while (str[len] != '\0') {
            len++;
        }
    }
    return len;
}

char *string_filter(const char *str, char c) {
    size_t length = string_length(str);
    size_t dist_c = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] != c) {
            dist_c++;
        }
    }
    char *str_filtrado = NULL;
    str_filtrado = (char*)malloc(sizeof(char)*(dist_c+1));
    size_t pos = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] != c) {
            str_filtrado[pos] = str[i];
            pos++;
        }
    }
    str_filtrado[dist_c] = '\0';
    return str_filtrado;
}

bool string_is_symmetric(const char *str) {
    bool symmetric = true;
    size_t length = string_length(str);
    unsigned int lft = 0;
    unsigned int rgt = length-1;
    while (lft < rgt && symmetric && rgt > 0) {
        if (str[lft] != str[rgt]) {
            symmetric = false;
        }
        lft++;
        rgt--;
    }
    return symmetric;
}