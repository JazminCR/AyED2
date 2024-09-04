#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    /*
     * COMPLETAR
     */
    struct s_node* first; // first es un puntero a struct s_node
    unsigned int size;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
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
    q->first = NULL;
    q->size = 0;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->first==NULL) {
        q->first = new_node;
    } else {
        struct s_node* aux = NULL; // puntero a un nodo (igual que first)
        aux = q->first;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = new_node;
    }
    q->size++;
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q->size;
    return size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;

}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

queue queue_copy(queue q) {
    assert(invrep(q));
    queue new_q = queue_empty();
    struct s_node *node=q->first;
    while(node!=NULL) {
        new_q = queue_enqueue(new_q, node->elem);
        node = node->next;
    }
    assert(invrep(q) && invrep(new_q));
    return new_q;

    /*
    queue q_copy = queue_empty();
    if (q->first == NULL) {
        return q_copy;
    }

    q->copy->first = create_node(q->first->elem);
    struct s_node *current_copy = q_copy->first;

    struct s_node *current = q->first->next;
    while (current != NULL) {
        current_copy->next = create_node(current->elem);
        current_copy = current_copy->next;
        current = current->next;
    }

    q_copy->size = q->size;
    return q_copy;
    
    */
}

queue queue_insert_at(queue q, queue_elem e, unsigned int pos) {
    assert(invrep(q) && pos <= q->size);

    struct s_node *new_node = create_node(e);

    if (pos == 0) {
        new_node->next = q->first;
        q->first = new_node;
    } else {
        struct s_node *aux = q->first;
        for (unsigned int i = 0; i < pos - 1; i++) {
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }
    
    q->size++;
    assert(invrep(q));
    return q;
}

queue queue_remove_at(queue q, unsigned int pos) {
    assert(invrep(q) && pos < q->size);

    struct s_node *killme = NULL;

    if (pos == 0) {
        killme = q->first;
        q->first = q->first->next;
    } else {
        struct s_node *aux = q->first;
        for (unsigned int i = 0; i < pos - 1; i++) {
            aux = aux->next;
        }
        killme = aux->next;
        aux->next = killme->next;
    }

    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}