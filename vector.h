#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include "nstl-types.h"

// Concatenates two vectors
#define concat(V1, V2) insert_vector(V1,V2,V1->size)

struct Vector;

typedef struct Vector Vector;

/*
 * Creates a new vector.
 */
extern struct Vector* vector( size_t typesize, unsigned int icap );

/*
 * Creates a vector from an array. Requires exact vector size (alloc'd area),
 * element size (sizeof) and number of elements, counting from 0.
 */
extern struct Vector* atov( void* array, size_t alloced, size_t typesize, unsigned int size );

/*
 * Works exactly like atov, but takes ownership of the passed array and uses it
 * for its underlying data. Avoids copying.
 */
extern struct Vector* atovown( void* array, size_t alloced, size_t typesize, unsigned int size );

/*
 * Insert an element at the back of the vector. Copies the void* content
 */
extern void push( struct Vector*, void* );

/*
 * Works like the [] operator - looks up element index in the vector.
 * Checks for boundry errors. Returns a pointer to, not a copy. See get.
 */
extern void* at( struct Vector*, unsigned int );

/*
 * Works like the [] operator - looks up element index in the vector.
 * Checks for boundry errors. Returns a copy, not a pointer to the element.
 * Remember to free
 */
extern void* get( struct Vector*, unsigned int );

/*
 * Inserts the elements from vector ins into vector orig at position pos.
 */
extern void insert_vector( struct Vector* orig, struct Vector* ins, unsigned int pos );

/*
 * Returns the vector size
 */
extern unsigned int vector_size( struct Vector* );

/*
 * Takes a destruction function pointer that is called on every element that
 * deallocs their heap data properly. Send in a useless dummy function for
 * simple types without heap memory. Frees the vectors memory. Always returns
 * NULL
 */
extern void* destroy_vector( struct Vector* V, destructor );

#endif //VECTOR_H
