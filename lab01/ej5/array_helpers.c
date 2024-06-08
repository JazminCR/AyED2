#include "array_helpers.h"
#include "mybool.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    FILE *fp = NULL;
    unsigned int array_length = 0;
    fp = fopen(filepath, "r");
    assert(fp != NULL);
    fscanf(fp, "%u", &array_length);
    assert(array_length <= max_size);
    for (unsigned int i=0; i < array_length; i++) {
        fscanf(fp, "%d", &array[i]);
        if (feof(fp) != 0) {
            printf("Error invalid (EOF)\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
    return array_length;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    if (length > 0) {
        for (unsigned int i=0; i < length-1; i++) {
            printf("%d, ", a[i]);
        }
        printf("%d", a[length-1]);
    }
    printf("]\n");
}

mybool array_is_sorted(int a[], unsigned int max_size) {
    mybool is_sorted = true;
    if (max_size != 0) {
        for (unsigned int i=0; i < max_size-1; i++) {
            is_sorted = is_sorted && (a[i] <= a[i+1]);
        }
    }
    return is_sorted;
}