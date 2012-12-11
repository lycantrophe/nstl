#include <stdlib.h>
#ifndef VECTOR_H
#define VECTOR_H

typedef unsigned short (*cmp)(void*,void*);

typedef struct {
    void *base;
    unsigned int size;
    size_t capacity;
    size_t item_size;
} Vector;

/*
 * Creates a new vector.
 */
extern Vector* vector( size_t typesize, size_t icap );

/*
 * Insert an element at the back of the vector.
 */
extern void push( Vector*, void* );

/*
 * Binary search the vector, looking for the target element. Takes a function
 * pointer to a comparison function that should return positive if the first
 * argument is less than the second argument.
 */
extern void* find( Vector*, cmp lt, void* target );

#endif //VECTOR_H
