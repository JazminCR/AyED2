#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_queue * queue;

typedef int queue_elem;

queue queue_empty(void);

bool queue_is_empty(queue q);

unsigned int queue_size(queue q);

void queue_dump(queue q, FILE *file);

queue_elem queue_first(queue q);

queue_elem queue_last(queue q);

queue queue_enqueue_first(queue q, queue_elem e);

queue queue_enqueue_last(queue q, queue_elem e);

queue queue_dequeue_first(queue q);

queue queue_dequeue_last(queue q);

queue queue_destroy(queue q);

queue queue_copy(queue q);

#endif
