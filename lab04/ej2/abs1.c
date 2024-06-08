#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0) {
        y = x;
    } else {
        y = -x;
    
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;
    absolute(a, res);
    printf("%d\n",res);
    return EXIT_SUCCESS;
}

// el valor que se muestra por consola es 0 ya que absolute no devuelve nada, 
// entonces el valor que se tiene de res es el declarado en main, que es 0
// no coincide con el del teórico, debería ser 10
