#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    stack s = stack_empty();
    s = stack_push(s, 3);
    stack_elem e = stack_top(s);
    printf("Primero: %u\n", e);

    s = stack_pop(s); // funciona bien para pilas de 1 elem
    unsigned int l = stack_size(s);
    printf("Long: %u\n", l);
    //e = stack_top(s);   salta assert porque s == NULL
    //printf("Primero: %u\n", e);

    s = stack_push(s, 7); // puede insertar elem si la pila quedó vacía
    e = stack_top(s);
    l = stack_size(s);
    printf("Primero: %u\n", e);
    printf("Long: %u\n", l);

    s = stack_destroy(s);

    stack pru = stack_empty();
    //pru = stack_push(pru, 1);
    stack_elem *a = stack_to_array(pru);
    //printf("Arreglo: %u\n", a[0]); segmentation fault porque a es null
    printf("%d\n", a == NULL); // verdadero, devuelve null para pila vacía

    pru = stack_destroy(pru);
    free(a); // liberar memoria de un arreglo

    return EXIT_SUCCESS;
}