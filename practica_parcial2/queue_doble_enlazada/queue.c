#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    /*
     * COMPLETAR
     */
    unsigned int size;
    struct s_node* first; // first es un puntero a struct s_node
    struct s_node* last;
};

struct s_node {
    queue_elem elem;
    struct s_node *prev;
    struct s_node *next;
};

// typedef struct s_node * node;  en vez de poner struct s_node *node, se puede poner node

static struct s_node * create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    node->prev=NULL;
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q=NULL;
    /*
     * COMPLETAR
     *
     */
    q = malloc(sizeof(struct s_queue));
    assert(q!=NULL);
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    //return q->first == NULL;
    return q->size == 0;
}

unsigned int queue_size(queue q) {
    assert(invrep(q));
    return q->size;
}

void queue_dump(queue q, FILE *file) {
    assert(invrep(q));
    struct s_node *current = q->first;
    while (current != NULL) {
        fprintf(file, "%d ", current->elem);
        current = current->next;
    }
    fprintf(file, "\n");
}

// obtener el primer elemento
queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}

// obtener el último elemento
queue_elem queue_last(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->last->elem;
}

// agregar un elemento al principio
queue queue_enqueue_first(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->first == NULL) {
        q->first = new_node;
        q->last = new_node;
    } else {
        new_node->next = q->first;
        q->first->prev = new_node;
        q->first = new_node;
    }
    q->size++;
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

// agregar un elemento al final
queue queue_enqueue_last(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->last == NULL) {
        q->first = new_node;
        q->last = new_node;
    } else {
        new_node->prev = q->last;
        q->last->next = new_node;
        q->last = new_node;
    }
    q->size++;
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

// quitar el primer elemento
queue queue_dequeue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node *killme = q->first;

    if (q->first == q->last) {
        q->first = NULL;
        q->last = NULL;
    } else {
        q->first = q->first->next;
        q->first->prev = NULL;
    }

    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

// quitar el último elemento
queue queue_dequeue_last(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node *killme = q->last;

    if (q->first == q->last) {
        q->first = NULL;
        q->last = NULL;
    } else {
        q->last = q->last->prev;
        q->last->next = NULL;
    }

    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    while (!queue_is_empty(q)) {
        q = queue_dequeue_first(q);
    }
    free(q);
    q=NULL;
    assert(q==NULL);
    return q;
}

queue queue_copy(queue q) {
    assert(invrep(q));
    queue new_q = queue_empty();
    struct s_node *current = q->first;
    while (current != NULL) {
        new_q = queue_enqueue_last(new_q, current->elem);
        current = current->next;
    }
    assert(invrep(q) && invrep(new_q) && queue_size(q) == queue_size(new_q));
    return new_q;
}
