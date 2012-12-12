#ifndef DEQUE_H
#define DEQUE_H

#include "list.h"

/*
 * O(1) linked list dequeue implementation.
 */

typedef struct {
    unsigned int size;
    List* head;
    List* tail;
} Deque;

/*
 * Constructs a default Deque object.
 */
extern Deque* deque( void );

/*
 * Enqueues a node with the given payload.
 */
extern void deenqueue( Deque*, void* );

/*
 * Shifts the first item from the dequeue and returns its payload. Reduces size
 * by one. Will fail if queue is empty.
 */
extern void* dedequeue( Deque* );

#endif //DEQUE_H
