#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x >= 0) {
        *y = x;
    } else {
        *y = -x;
    
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    a = -10;
    absolute(a, &res);
    assert(res >= 0 && (res == a || res == -a));
    printf("%d\n",res);
    return EXIT_SUCCESS;
}

// se muestra como valor 10
// se cambió absolute para que reciba un puntero a int, y se le pasa la dirección de memoria de res, 
// entonces se guarda la modificación que realiza absolute en esa direc de memoria

// el parámetro int *y de absolute es de tipo in
