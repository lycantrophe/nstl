#ifndef STACK_H
#define STACK_H
#include "vector.h"

#define stack(typesize, icap) vector(typesize,icap);

typedef Stack Vector

/*
 * The stack, a FIFO priority queue, extends the vector by adding the pop
 * method.
 */
extern void* pop( Stack* V );
extern void push( Stack );

#endif //STACK_H
