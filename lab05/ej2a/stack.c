#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

// inv de rep: propiedad siempre verdadera para la implementación
// func de inv: se llama al principio y al final, con assert
/* ejemplo:
    stack fun(stack s) {
        assert(invrep(s));  // asegura recibir algo ok
        ...
        implemetación
        ...
        assert(invrep(s));  // asegura devolver algo ok
        return s;
    }
    en el constructor se chequea al final, 
    y en el destructor al inicio.
*/
 
struct _s_stack {
    stack_elem elem;
    stack next;
};

stack stack_empty() {
    return NULL;
}

stack stack_push(stack s, stack_elem e) {
    stack new = malloc(sizeof(struct _s_stack));
    new->elem = e;
    new->next = s;
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
    stack aux = s;
    unsigned int len = 0;
    while (aux != NULL) {
        len++;
        aux = aux->next;
    }
    return len;
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

    /*
    profe Santi
    while (s != NULL) {
        stack aux = s;
        s = aux->next;
        aux->next = NULL;
        free(aux);
    }
    */