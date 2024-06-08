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
    unsigned int length1 = fstring_length(s1);
    unsigned int length2 = fstring_length(s2);
    unsigned int i  = 0;

    if (length1 == length2) {
        while (i < length1 && equal) {
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

    bool menor = true;
    unsigned int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        i++;
    }

    if (s1[i] > s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        menor = false;
    } else if (s2[i] == '\0') {
        menor = false;
    }
    return menor;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
    
}


