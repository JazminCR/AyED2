#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    //scanf("%s", user_input); termina la lectura cuando encuentra un espacio

    char *input = fgets(user_input, MAX_LENGTH, stdin); // lee hasta MAX_LENGTH-1 caracteres
    // user_input: puntero a un arreglo de caracteres donde se almacenará la línea leída.
    // MAX_LENGTH: tamaño max de caracteres que se pueden leer, incluyendo '\0'.
    // stdin: desde donde se leerá la línea (entrada estandar, teclado.)
    
    if (input == NULL) {
        fprintf(stderr, "Error al leer la entrada\n");
        return EXIT_FAILURE;
    }

    user_input[string_length(user_input)-1] = '\0'; // elimina el salto de línea
    // strlen(user_input): devuelve la longitud de la cadena user_input.
    // al restarle 1 se accede al último elemento de la cadena, el cual es '\n' 
    // porque así funciona fgets, entonces lo cambia por '\0'

    filtered = string_filter(user_input, ignore_chars[0]);
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        char *aux = string_filter(filtered, ignore_chars[i]);
        free(filtered);
        filtered = aux;
    }

    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");
    
    free(filtered);
    
    return EXIT_SUCCESS;
}

