#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>

#define EXTRA_ALLOC_LIMIT 32

// Concatenates two vectors
#define concat(V1, V2) insert_vector(V1,V2,V1->size)

typedef struct {
    void* base;
    unsigned int size;
    size_t capacity;
    size_t item_size;
} Vector;

/*
 * Creates a new vector.
 */
extern Vector* vector( size_t typesize, unsigned int icap );

/*
 * Insert an element at the back of the vector.
 */
extern void push( Vector*, void* );

/*
 * Works like the [] operator - looks up element index in the vector.
 * Checks for boundry errors. Returns a pointer to, not a copy. See get.
 */
extern void* at( Vector*, unsigned int );

/*
 * Works like the [] operator - looks up element index in the vector.
 * Checks for boundry errors. Returns a copy, not a pointer to the element.
 * Remember to free
 */
extern void* get( Vector*, unsigned int );

/*
 * Inserts the elements from vector ins into vector orig at position pos.
 */
extern void insert_vector( Vector* orig, Vector* ins, unsigned int pos );

#endif //VECTOR_H
