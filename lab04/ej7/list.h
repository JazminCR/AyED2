#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* counter as a pointer to structs to guarantee encapsulation */
typedef struct _list * list;
typedef int list_elem;

/* Constructors */
list empty(void);
/*
    Create a empty list.
*/

list addl(list_elem e, list l);
/*
    Add element e to the left of the list l.
*/


/* Operations */
bool is_empty(list l);
/*
    Return True if the list is empty, False otherwise.
*/

list_elem head(list l);
/*
    Return the first element of the list l.
*/

list tail(list l);
/*
    Return the list l without the first element.
*/

list addr(list_elem e, list l);
/*
    Add element e to the right of the list l.
*/

unsigned int length(list l);
/*
    Return the length of the list l.
*/

list concat(list l, list c);
/*
    Add to the end of the list l the list c in the same orden.
*/

list_elem index(list l, unsigned int i);
/*
    Return the element at position i in the list l.
*/

list take(list l, unsigned int n);
/*
    Return the list with the first n elements of the list l.
*/

list drop(list l, unsigned int n);
/*
    Return the list without the first n elements of the list l.
*/

list copy(list l);
/*
    Return a copy of the list l.
*/

list destroy(list l);
/*
    Free the memory allocated for the list l.
*/

#endif
