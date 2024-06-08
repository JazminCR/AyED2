#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int indice = 0;
    while (s[indice] != '\0') {
        indice++;
    }
    return indice;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool equal = true;
    unsigned int len1 = fstring_length(s1);
    unsigned int len2 = fstring_length(s2);
    unsigned int i = 0;

    if (len1 == len2) {
        while (i < len1 && equal) {
            if (s1[i] == s2[i]) {
                equal = true;
            } else {
                equal = false;
            }
            i++;
        }
    } else {
        equal = false;
    }
    return equal;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool less_eq = true;
    unsigned int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        i++;
    }
    if (s1[i] > s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        less_eq = false;
    } else if (s2[i] == '\0') {
        less_eq = false;
    }
    return less_eq;
} 

