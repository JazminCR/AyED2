#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

int main() {
    string str1 = string_create("hola");
    string str2 = string_create("chau");
    string str3 = string_create("hola");
    string str4 = string_create("mañana");

    printf("hola es menor que chau? %i\n", string_less(str1, str2));
    printf("mañana es menor que hola? %i\n", string_less(str4, str1));
    printf("hola es menor que mañana? %i\n", string_less(str1, str4));
    printf("hola es igual que chau? %i\n", string_eq(str1, str2));
    printf("chau es igual que chau? %i\n", string_eq(str2, str2));

    str1 = string_destroy(str1);
    str2 = string_destroy(str2);
    str3 = string_destroy(str3);
    str4 = string_destroy(str4);
    return(EXIT_SUCCESS);
} 