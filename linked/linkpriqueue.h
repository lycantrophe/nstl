#ifndef LINKPRIQUEUE_H
#define LINKPRIQUEUE_H

#include "list.h"

/*
 * Defines the common data structure for deques and stacks
 */

typedef struct {
    unsigned int size;
    List* head;
    List* tail;
} Lpriqueue;

#endif //LINKPRIQUEUE_H
