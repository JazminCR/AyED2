#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    /*
     * COMPLETAR
     *
     */
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    /*
     * COMPLETAR
     *
     */
    pstack_elem elem;
    priority_t prio;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    /*
     * COMPLETAR
     */
    new_node->elem = e;
    new_node->prio = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    /*
     * COMPLETAR
     *
     */
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    /*
     * COMPLETAR
     *
     */
    bool inv = (s != NULL); // verifica la existencia de la pila
    if (inv && s->size != 0 && s->first != NULL) { // verifica que la pila no esté vacía
        struct s_node *p = s->first; // para recorrer la pila
        unsigned int lenght = 1;     // para contar la cantidad de nodos
        while (p->next != NULL) {  
            inv = inv && p->prio >= p->next->prio; // verifica que la prioridad del nodo actual sea mayor o igual a la del siguiente 
            p = p->next;            // avanza al siguiente nodo
            lenght++;               // incrementa la cantidad de nodos
        }
        inv = inv && lenght == s->size; // verifica que la cantidad de nodos sea igual al tamaño de la pila
    }
    return true;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    /*
     * COMPLETAR
     *
     */
    s = malloc(sizeof(struct s_pstack));
    s->size = 0;
    s->first = NULL;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    /*
     * COMPLETAR
     *
     */
    if (s == NULL) {
        s->size = 1;
        s->first = new_node;
    } else {
        struct s_node *p = NULL;
        struct s_node *q = NULL;
        p = s->first;

        while (p != NULL && p->prio > priority) {
            q = p;
            p = p->next;
        }

        new_node->next = p;

        if (q != NULL) {
            q->next = new_node;
        } else {
            s->first = new_node;
        }
        s->size++;
    }
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    /*
     * COMPLETAR
     *
     */
    return s->first == NULL;
}

pstack_elem pstack_top(pstack s) {
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s) {
    /*
     * COMPLETAR
     *
     */
    return s->first->prio;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size=0;
    size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    /*
     * COMPLETAR
     *
     */
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *p = s->first;
    s->first = s->first->next;
    p = destroy_node(p);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    /*
     * COMPLETAR
     *
     */
    struct s_node *p = NULL;
    p = s->first;
    while (p != NULL) {
        struct s_node *q = p;
        p = p->next;
        q = destroy_node(q);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

