#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_upperbound = true;
    res.is_lowerbound = true;
    res.exists = false;
    unsigned int i;
    i=0;
    while (i < length) {
        if (value < arr[i]) {
            res.is_upperbound = false;
        }
        if (value > arr[i]) {
            res.is_lowerbound = false;
        }
        if (value == arr[i] && res.exists == false) {
            res.exists = true;
            res.where = i;
        }
        i=i+1;
    }
    return res;
}

int main(void) {
    // int a[ARRAY_SIZE] = {0, -1, 9, 4};
    // int value=9;
    int a[ARRAY_SIZE];
    int j=0;
    while (j < ARRAY_SIZE){
	    printf("Ingrese el elemento %d del arreglo:\n",j);
	    scanf("%d",&a[j]);
	    j=j+1;
    }
    int value;
    printf("Ingrese un valor para value\n");
    scanf("%d", &value);
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    if (result.is_upperbound == 1 && result.exists == 0) {
        printf("Value es cota superior\n");
    }
    if (result.is_lowerbound == 1 && result.exists == 0) {
        printf("Value es cota inferior\n");
    }
    if (result.is_upperbound == 1 && result.exists == 1) {
        printf("Value es maximo\n");
        printf("La posicion de value es %u\n", result.where);
    }
    if (result.is_lowerbound == 1 && result.exists == 1) {
        printf("Value es minimo\n");
        printf("La posicion de value es %u\n", result.where);
    }
    return EXIT_SUCCESS;
}

