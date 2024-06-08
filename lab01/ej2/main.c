/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

int array_from_stdin(int array[], unsigned int max_size) {
    unsigned int i=0;
    fprintf(stdout, "Ingrese la cantidad de elementos del arreglo: ");
    fscanf(stdin, "%u", &max_size);

    while (!feof(stdin) && i < max_size) {
        fprintf(stdout, "Ingrese el valor del elemento %u: \n", i+1);
        fscanf(stdin, "%d", &array[i]);
        i++;
    }

    fprintf(stdout, "El tamaño del arreglo es: %u \n", max_size);
    return max_size;
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


int main() {
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
