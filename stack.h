#ifndef STACK_H
#define STACK_H
#include "vector.h"

/*
 * The stack, a FIFO priority queue, extends the vector by adding the pop
 * method.
 */
extern void* pop( Vector* V );

#endif //STACK_H
