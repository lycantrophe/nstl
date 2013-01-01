#ifndef DEQUE_H
#define DEQUE_H

#include "list.h"

/*
 * O(1) linked list dequeue implementation.
 */

struct Lpriqueue;
typedef struct Lpriqueue Deque;


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

/*
 * Pops and returns the payload of the last element in the queue
 */
extern void* depop( Deque* );

#endif //DEQUE_H
