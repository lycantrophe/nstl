#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>
#include "vector.h"
#include "assert.h"

typedef struct {
    Vector *V;
    void* first;
} Queue;

void enqueue(Queue*, void*);
void* dequeue(Queue*);

#endif

