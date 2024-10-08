/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    if (x->rank > y->rank) {
        return false;
    }
    return true;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned int i, unsigned int j) {
    player_t aux;
    aux = a[i]; a[i] = a[j]; a[j] = aux;
}

void insert(player_t a[], unsigned int i) { 
    unsigned int j;
    j = i;
    while (j>0 && goes_before(a[j],a[j-1])) {
        swap(a,j-1,j); 
        j--;
    }
    
}

void sort(player_t a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        assert(array_is_sorted(a,i));
        insert(a, i);
    }
}

// demora sin punteros: 0.150895 seconds
// demora con punteros: 0.042072 seconds
// la dif se debe a que con punteros se manipula directamente la direccion de memoria de los elementos del array, 
// mientras que sin punteros se copian los elementos de un array a otro, lo que lleva mas tiempo
