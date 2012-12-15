#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"
#include "vector-private.h"

Vector* __initialize_vector( Vector* V, size_t typesize, unsigned int icap ) {
    V->base = malloc( icap * typesize );
    V->capacity = icap * typesize;
    V->size = 0;
    V->item_size = typesize;
    return V;
}

Vector* vector( size_t typesize, unsigned int icap ) {
    return __initialize_vector( malloc( sizeof( Vector ) ), typesize, icap );
}

void push( Vector* V, void* item ) {
    /* When all free slots have been filled -
     * double capacity.
     */
    if( V->item_size * V->size == V->capacity ) {
        V->capacity *= 2;
        V->base = realloc( V->base, V->capacity );
    }

    /* Make a copy of the item and insert into the vector */
    void* dst = ((char*)V->base) + V->item_size * V->size;
    memcpy( dst, item, V->item_size );
    ++V->size;
}

void* at( Vector* V, unsigned int index ) {
    assert( index <= V->size );
    return (char*)V->base + ( V->item_size * index );
}

void* get( Vector* V, unsigned int index ) {
    assert( index <= V->size );
    return memcpy( malloc( V->item_size ), at( V, index ), V->item_size );
}

void insert_vector( Vector* orig, Vector* ins, unsigned int pos ) {
    assert( orig->item_size == ins->item_size );
    assert( pos <= orig->size );

    // Just a convenience variable to enhance readability
    size_t size = orig->item_size; 

    size_t new_capacity = orig->capacity;
    void* base = orig->base;

    /* Do we need more memory? */
    if( ( orig->size + ins->size ) * size >= orig->capacity )
        new_capacity = ( orig->size + ins->size ) * size;

    if( new_capacity - EXTRA_ALLOC_LIMIT <= size *( orig->size + ins->size ) )
        new_capacity *= 2;

    /* move the first pos elements */
    if( new_capacity != orig->capacity )
        base = memmove( malloc( new_capacity ), base, pos * size );

    /* Moves the right part of the vector, making a hole in the middle */
    memcpy( (char*)base + ( pos + ins->size ) * size,
            (char*)orig->base + ( pos * size ), ( orig->size - pos ) * size );

    /* Place the new vector in between */
    memmove( (char*)base + ( pos * size ), ins->base, ins->size * size );

    free( orig->base );
    orig->base = base;
    orig->capacity = new_capacity;
    orig->size = orig->size + ins->size;
}
