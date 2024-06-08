#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    stack next;
    unsigned int size;
};

stack stack_empty() {
    return NULL;
}

stack stack_push(stack s, stack_elem e) {
    stack new = malloc(sizeof(struct _s_stack));
    new->elem = e;
    new->next = s;
    new->size = s == NULL ? 1 : s->size + 1;
    s = new;
    return s;
}

stack stack_pop(stack s) {
    assert(s != NULL);
    stack aux = s;
    s = s->next;
    free(aux);
    return s;
}

unsigned int stack_size(stack s) {
    return s == NULL ? 0 : s->size;
}

stack_elem stack_top(stack s) {
    assert(s != NULL);
    return s->elem;
}

bool stack_is_empty(stack s) {
    return s == NULL;
}

//devuelve un puntero a stack_elem
stack_elem *stack_to_array(stack s) {
    if (s != NULL) {
        unsigned int long_stack = stack_size(s);
        stack_elem *array = NULL;
        // calloc pide memoria -> recordar hacer free en el main desp d usarla
        array = calloc(long_stack, sizeof(stack_elem));
        while (long_stack--) {
            array[long_stack] = s->elem;
            s = s->next;
        }
        return array;
    } else {
        return NULL;
    }
}

stack stack_destroy(stack s) {
    while (s != NULL) {
        stack aux = s;
        s = s->next;
        free(aux);
    }
    return s; 
}