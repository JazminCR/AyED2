#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n",
           sizeof(messi.name),
           sizeof(messi.age),
           sizeof(messi.height),
           sizeof(messi));

    name_t *n = NULL;
    n = &messi.name;
    unsigned int *a = NULL;
    a = &messi.age;
    unsigned int *h = NULL;
    h = &messi.height;
    
    printf("name-add: %p\n", (void *) n);
    printf("age-add: %p\n", (void *) a);
    printf("height-add: %p\n", (void *) h);
    printf("name-index: %lu\n", (uintptr_t) n);
    printf("age-index: %lu\n", (uintptr_t) a);
    printf("height-index: %lu\n", (uintptr_t) h);

    return EXIT_SUCCESS;
}

// name = 30 bytes
// age = 4 bytes
// height = 4 bytes
// data_t = 40 bytes

// la suma no coincide 38 != 40
// el tamaño de name no depende del nombre que tenga
