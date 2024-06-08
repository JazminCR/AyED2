#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "fixstring.h"

void swap(fixstring a[], unsigned int i, unsigned int j) {
    fixstring aux;
    fstring_set(aux, a[i]);
    fstring_set(a[i], a[j]);
    fstring_set(a[j], aux);
}

bool goes_before(fixstring x, fixstring y) {
    if (fstring_length(x) < fstring_length(y)) {
        return true;
    } else if (fstring_length(x) > fstring_length(y)) {
        return false;
    }

    for (unsigned int i = 0; i < fstring_length(x); i++) {
        if (x[i] < y[i]) {
            return true;
        } else if (x[i] > y[i]) {
            return false;
        }
    }
    return false;
}

bool array_is_sorted(fixstring array[], unsigned int length) {
    unsigned int i = 1;
    while (i < length && goes_before(array[i-1], array[i])) {
        i++;
    }
    return (i >= length);
}

