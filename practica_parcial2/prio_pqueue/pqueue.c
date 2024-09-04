#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    /*
     * COMPLETAR
     *
     */
    struct s_node *first;
    unsigned int size;
     
};

struct s_node {
    /*
     * COMPLETAR
     *
     */
    pqueue_elem elem;
    unsigned int prio;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    // Completar
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    /*
     * COMPLETAR
     */
    new_node->elem = e;
    new_node->prio = priority;
    new_node->next = NULL;
    assert(e==e && priority == priority); // BORRAR ESTE ASSERT
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


static bool invrep(pqueue q) {
    /*
     * COMPLETAR
     *
     */
    bool inv = (q != NULL);
    if (inv && q->size != 0 && q->first != NULL) {
        struct s_node *p = q->first;
        unsigned int length = 1;
        while (p->next != NULL) {
            inv = inv && p->prio <= p->next->prio;
            p = p->next;
            length++;
        }
        inv = inv && length == q->size;
    }
    return inv;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    /*
     * COMPLETAR
     *
     */
    q = malloc(sizeof(struct s_pqueue));
    q->first = NULL;
    q->size = 0;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    /*
     * COMPLETAR
     *
     */
    if (q == NULL) {
        q->first = new_node;
        q->size = 1;
    } else {
        struct s_node *p = NULL;
        struct s_node *s = NULL;
        p = q->first;

        while (p != NULL && p->prio <= priority) {
            s = p;
            p = p->next;
        }

        new_node->next = p;

        if (s != NULL) {
            s->next = new_node;
        } else {
            q->first = new_node;
        }
        q->size++;
    }
    
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    /*
     * COMPLETAR
     *
     */
    return q->first == NULL;
}

pqueue_elem pqueue_peek(pqueue q) {
    /*
     * COMPLETAR
     *
     */
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    /*
     * COMPLETAR
     *
     */
    return q->first->prio;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0;
    /*
     * COMPLETAR
     *
     */
    size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    /*
     * COMPLETAR
     *
     */
    struct s_node *p = q->first;
    q->first = q->first->next;
    p = destroy_node(p);
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    /*
     * COMPLETAR
     *
     */
    struct s_node *p = q->first;
    while (p != NULL) {
        struct s_node *s = p;
        p = p->next;
        s = destroy_node(s);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

// agregada

pqueue pqueue_copy(pqueue q) {
    assert(invrep(q));
    pqueue copy = pqueue_empty();
    struct s_node *p = q->first;
    while (p != NULL) {
        copy = pqueue_enqueue(copy, p->elem, p->prio);
        p = p->next;
    }
    assert(invrep(q) && invrep(copy));
    return copy;

    /*
    sin usar enqueue

    pqueue copy = pqueue_empty();
    if (q->first == NULL) {
        return copy;
    }

    copy->first = create_node(q->first->elem, q->first->prio);
    struct s_node *current_copy = q->first->next;

    struct s_node *current_original = q->first->next;    
    while (current_original != NULL) {
        current_copy->next = create_node(current_original->elem, current_original->prio);
        current_copy = current_copy->next;
        current_original = current_original->next;
    }

    copy->size = q->size;
    assert(invrep(q) && invrep(copy));
    return copy;
    
    */
}
