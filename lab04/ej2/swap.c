#include <stdlib.h>
#include <stdio.h>

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

int main(void) {
    int a=0, b=0;
    a = 5;
    b = 10;
    printf("Original: a = %d, b = %d\n",a,b);
    swap(&a, &b);
    printf("Con swap: a = %d, b = %d\n",a,b);
    return EXIT_SUCCESS;
}
