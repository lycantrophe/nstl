#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>

// Concatenates two vectors
#define concat(V1, V2) insert_vector(V1,V2,V1->size)

struct Vector;

typedef struct Vector Vector;

/*
 * Creates a new vector.
 */
extern struct Vector* vector( size_t typesize, unsigned int icap );

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
extern void* destroy_vector( struct Vector* V, void (*)( void* ) );

#endif //VECTOR_H
