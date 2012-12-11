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

extern Vector* vector( size_t typesize, size_t icap );
extern void push( Vector*, void* );
extern void* find( Vector*, cmp lt, void* target );

#endif //VECTOR_H
