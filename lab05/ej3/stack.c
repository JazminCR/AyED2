#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

// if new->capacity > 0 --> new->elems != NULL
static bool invrep(stack s) {
    return s != NULL && s->capacity >= s->size;
}

stack stack_empty() {
    stack new = malloc(sizeof(struct _s_stack));
    new->elems = NULL;
    new->size = 0;
    new->capacity = 0;
    assert(invrep(new));
    return new;
}

// Elemento en la parte sup de la pila
stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    if (s->size == s->capacity) {
        // Pedir más memoria
        s->capacity = (s->capacity == 0) ? 1 : s->capacity * 2;
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
        assert(s->elems != NULL);
    }
    s->elems[s->size] = e;
    s->size++;
    assert(invrep(s));
    return s;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    if (s->size > 0) {
        s->size--;
    }
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
}

// Elemento de la parte superior de la pila
stack_elem stack_top(stack s) {
    assert(s->size > 0); 
    assert(invrep(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s->size == 0;
}

stack_elem *stack_to_array(stack s) {
    assert(invrep(s));
    stack_elem *array = malloc(s->size * sizeof(stack_elem));
    assert(array != NULL);
    for (unsigned int i = 0; i < s->size; i++) {
        array[i] = s->elems[i];
    }
    assert(invrep(s));
    return array;
}

stack stack_destroy(stack s) {
    assert(invrep(s));
    free(s->elems);
    free(s);
    return NULL;
}