#ifndef STACK_H
#define STACK_H
#include "vector.h"

#define stack(typesize, icap) vector(typesize,icap)
#define destroy_stack(stack, destructor) destroy_vector(stack, destructor)

typedef Vector Stack;

/*
 * The stack, a FIFO priority queue, extends the vector by adding the pop
 * method.
 */
extern void* pop( Stack* );
extern void push( Stack*, void* );

#endif //STACK_H
