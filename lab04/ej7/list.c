#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct _list {
    list_elem elem;
    list next;
};

list empty(void) {
    list l = NULL;
    return l;
}

list addl(list_elem e, list l) {
    list new = malloc(sizeof(struct _list));
    new->elem = e;
    new->next = l;
    l = new;
    return l;
}

bool is_empty(list l) {
    return l == NULL;
}

list_elem head(list l) {
    assert(l != NULL);
    return l->elem;
}

list tail(list l) {
    assert(l != NULL);
    l = l->next;
    return l;
}

list addr(list_elem e, list l) {
    list p;
    list q = malloc(sizeof(struct _list));
    q->elem = e;
    q->next = NULL;
    if (l != NULL) {
        p = l;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = q;
    } else {
        l = q;
    }
    return l;
}

unsigned int length(list l) {
    list p = l;
    unsigned int n = 0;
    while (p != NULL) {
        n++;
        p = p->next;
    }
    return n;
}

list concat(list l, list c) {
    list aux;
    if (l != NULL) {
        aux = l;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = c;
    } else {
        l = c;
    }
    return l;
}

list_elem index(list l, unsigned int i) {
    assert(length(l) > i);
    list aux;
    unsigned int j = 0;
    while (j < i) {
        aux = l;
        l = aux->next;
        j++;
    }
    return l->elem;
}

list take(list l, unsigned int n) {
    if (n == 0) {
        return NULL;
    } else {
        list p;
        p = l;
        while (n > 1 && p != NULL) {
            p = p->next;
            n--;
        }
        p->next = NULL;
        return l;
    }
}

list drop(list l, unsigned int n) {
    list aux;
    unsigned int i = 0;
    while (i < n && l != NULL) {
        aux = l;
        l = aux->next;
        free(aux);
        i++;
    }
    return l;
}

list copy(list l) {
    list lc;
    if (l == NULL) {
        lc = NULL;
    } else {
        lc = malloc(sizeof(struct _list));
        lc->elem = l->elem;
        lc->next = copy(l->next);
    }
    return lc;
}

list destroy(list l) {
    if (l != NULL) {
        destroy(l->next);
        free(l);
        l = NULL;
    }
    return l;

  /*  while (l != NULL) {
        list aux=l;
        l = l->next;
        free(aux);
    }*/
}
