#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>
#include "vector.h"

typedef struct {
    Vector V;
    void* first;
} Queue;

/*
 * Creates a new queue
 */
extern Queue* queue( size_t typesize, unsigned int icap );
extern void enqueue( Queue*, void* );
extern void* dequeue( Queue* );

#endif //QUEUE_H
