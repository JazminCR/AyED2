#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        exit(EXIT_FAILURE);
    }
    result = argv[1];
    return result;
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {
    /* Read data from file and store it in indexes and letters arrays. */
    FILE *fp = NULL;
    fp = fopen(path, "r");
    assert(fp != NULL);
    unsigned int i = 0;
    int size = 0;
    while (!feof(fp) && i < max_size) {
        size = fscanf(fp, "%u -> *%c* ", &indexes[i], &letters[i]);
        if (size != 2) {
            printf("Error reading file.\n");
            return EXIT_FAILURE;
        }
        i++;
    }
    fclose(fp);
    return i;
}

char *sort(char letters[], unsigned int indexes[], char sorted[], unsigned int max_size) {
    unsigned int k = 0;
    for (unsigned int j = 0; j < max_size; j++) {
        k = indexes[j];
        if (k < max_size) {
            sorted[k] = letters[j];
        } else {
            printf("Index out of bounds.\n");
            exit(EXIT_FAILURE);
        }
    }
    return sorted;
}

int main(int argc, char *argv[]) {
    //FILE *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    
    char *filename = NULL;
    filename = parse_filepath(argc, argv);
    length = data_from_file(filename, indexes, letters, MAX_SIZE);
    sort(letters, indexes, sorted, length);
    dump(letters, length);
    dump(sorted, length);
    return EXIT_SUCCESS;
}

