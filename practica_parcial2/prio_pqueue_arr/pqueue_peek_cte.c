#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    /* COMPLETAR */
    unsigned int size;
    priority_t min_prio;
    struct s_node **array; // array es un puntero a un arreglo de punteros
    bool *priority_has_elem; // array para rastrear si hay elementos en la prioridad CTE
    priority_t current_min_prio; // prioridad mínima actual con elementos CTE
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    /* COMPLETAR */
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    /* COMPLETAR */
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool inv = (q != NULL);
    if (inv && q->size != 0 && q->array != NULL) {
        struct s_node *p;
        unsigned int length = 0;
        for (unsigned int i = 0; i <= q->min_prio; i++) {
            p = q->array[i];
            while (p != NULL) {
                length++;
                p = p->next;
            }
        }
        inv = inv && length == q->size;
    }
    return inv;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    /*
     * COMPLETAR
     *
     */
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    q->min_prio = min_priority;
    q->array = calloc(min_priority+1, sizeof(struct s_node*));
    q->priority_has_elem = calloc(min_priority+1, sizeof(bool));    // CTE
    q->current_min_prio = min_priority + 1;                         // CTE

    for (unsigned int i = 0; i <= min_priority; i++) {
        q->array[i] = NULL;
        q->priority_has_elem[i] = false;                            // CTE
    }

    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q) && priority <= q->min_prio);
    /*
     * COMPLETAR
     *
     */
    struct s_node *new_node = create_node(e);
    if (q->array[priority] == NULL) {
        q->array[priority] = new_node;
    } else {
        struct s_node *p = q->array[priority];
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = new_node;
    }

    if (!q->priority_has_elem[priority]) {                          // CTE
        q->priority_has_elem[priority] = true;                      // CTE
        if (priority < q->current_min_prio) {                       // CTE
            q->current_min_prio = priority;                         // CTE
        }                                                           // CTE
    }                                                               // CTE

    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    bool empty = true;
    for (unsigned int i = 0; i <= q->min_prio; i++) {
        empty = empty && q->array[i] == NULL;
    }
    return empty;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem e;
    unsigned int i = 0;
    while (q->array[i] == NULL) {
        i++;
    }
    e = q->array[i]->elem;
    assert(invrep(q));
    return e;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
 /*   priority_t p = 0;
    while (q->array[p] == NULL) {
        p++;
    }
    assert(invrep(q));
    return p; */
    return q->current_min_prio;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    /* COMPLETAR */
    priority_t p = pqueue_peek_priority(q);
    struct s_node *p_aux = q->array[p];
    q->array[p] = q->array[p]->next;
    p_aux = destroy_node(p_aux);

    if (q->array[p] == NULL) {                                      // CTE
        q->priority_has_elem[p] = false;                            // CTE
        for (priority_t i = p+1; i<= q->min_prio; i++) {            // CTE
            if (q->priority_has_elem[i]) {                          // CTE
                q->current_min_prio = i;                            // CTE
                break;                                              // CTE
            }                                                       // CTE
        }                                                           // CTE
    }                                                               // CTE

    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    /* COMPLETAR*/
    while( !pqueue_is_empty(q) ) {
        pqueue_dequeue(q);
    }
    free(q->array);
    free(q->priority_has_elem);                                     // CTE
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

// agregada

pqueue pqueue_copy(pqueue q) {
    assert(invrep(q));
    pqueue q_copy = pqueue_empty(q->min_prio);
    for (unsigned int i = 0; i <= q->min_prio; i++) {
        struct s_node *p = q->array[i];
        while (p != NULL) {
            q_copy = pqueue_enqueue(q_copy, p->elem, i);
            p = p->next;
        }
    }
    assert(invrep(q) && invrep(q_copy));
    return q_copy;
}