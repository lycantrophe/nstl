#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>
#include "vector.h"

struct Queue;
typedef struct Queue Queue;

/*
 * Creates a new queue
 */
extern Queue* queue( size_t typesize, unsigned int icap );
/*
 * Takes responsibility over the passed vector. Assumes that the first item is
 * at index 0.
 */
extern Queue* vtoq( Vector* V );
extern void enqueue( Queue*, void* );
/*
 * Returns a copy of the item, so every dequeued item requires explicit
 * free-ing
 */
extern void* dequeue( Queue* );

extern void* destroy_queue( Queue*, destructor );

#endif //QUEUE_H
