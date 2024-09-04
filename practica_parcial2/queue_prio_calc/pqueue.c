#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *front;
    
};

struct s_node {
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade, unsigned int approved_courses) {
    float prio;
    prio = 0.5 * (average_grade/MAX_GRADE) + 0.5 * (approved_courses/TOTAL_COURSES);
    assert(prio >= 0.0 && prio <= 1.0);
    return prio;
}

static struct s_node *create_node(pqueue_elem e, float average_grade, unsigned int approved_courses) {
    struct s_node *new_node = malloc(sizeof(struct s_node));

    float priority = calculate_priority(average_grade, approved_courses);

    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = priority;
    new_node->next = NULL;

    assert(new_node != NULL);
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q) {
    bool inv = (q != NULL);

    if (q->size > 1) {
        struct s_node *p = q->front;
        while (p->next != NULL && inv) {
            inv = (p->priority >= p->next->priority);
            p = p->next;
        }
    }
    return inv;
}

pqueue pqueue_empty(void) {
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    assert(q != NULL);

    q->size = 0u;
    q->front = NULL;
    
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, float average_grade, unsigned int approved_courses) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    float priority = calculate_priority(average_grade, approved_courses);

    if (q->size == 0) {     // si no hay elems, va primero
        q->front = new_node;
    } else if (priority > pqueue_peek_priority(q)) {    // si la prio del nodo a agregar es mayor a cualquiera otra de la cola, va primero
        new_node->next = q->front;
        q->front = new_node;
    } else {    // si no, se busca la posicion correcta
        struct s_node *p = q->front;
        while (p->next != NULL && priority <= p->next->priority) {
            p = p->next;
        }
        new_node->next = p->next;   // se agrega antes del primero con menor prioridad
        p->next = new_node;         // si no existe, se agrega al final

    }
    q->size ++;
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0;
}


pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    pqueue_elem e;
    e = q->front->elem;

    assert(invrep(q));
    return e;
}

float pqueue_peek_average_grade(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    float g;
    g = q->front->average_grade;

    assert(invrep(q));
    return g;
}

unsigned int pqueue_peek_approved_courses(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    unsigned int c;
    c = q->front->approved_courses;

    assert(invrep(q));
    return c;
}

float pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    float p;
    p = q->front->priority;

    assert(invrep(q));
    return p;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));

    unsigned int size = 0;
    size = q->size;
   
    return size;
}

pqueue pqueue_copy(pqueue q) {
    assert(invrep(q));
    
    pqueue copy = pqueue_empty();
    struct s_node *clone = q->front;

    while (clone != NULL) {
        copy = pqueue_enqueue(copy, clone->elem, clone->average_grade, clone->approved_courses);
        clone = clone->next;
    }

    assert(invrep(q));
    return copy;

    /*
    assert(invrep(q));
    pqueue copy = pqueue_empty();
    struct s_node *p = q->front;
    for (unsigned int i = 0; i < q->size; i++) {
        copy = pqueue_enqueue(copy, p->elem, p->average_grade, p->approved_courses);
        p = p->next;
    }
    assert(invrep(q) && invrep(copy)) && pqueue_size(q) == pqueue_size(copy);
    return copy;
    
    */
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    struct s_node *killme = q->front;
    q->front = q->front->next;
    killme = destroy_node(killme);
    q->size --;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    
    struct s_node *node = q->front;
    while (node != NULL) {
        struct s_node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;

    assert(q == NULL);
    return q;

    /*
    assert(invrep(q));
    while (!pqueue_is_empty(q)) {
        q = pqueue_dequeue(q);
    }
    q->front = NULL;
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
    */
}
