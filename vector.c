#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

Vector* vector( size_t typesize, size_t icap ) {
    Vector* V = malloc( sizeof( Vector ) );
    V->base = malloc( icap * typesize );
    V->capacity = icap;
    V->size = 0;
    V->item_size = typesize;
    return V;
}

void push( Vector* V, void* item ) {
    if( V->size == V->capacity ) {
        V->capacity *= 2;
        V->base = realloc( V->base, V->item_size * V->capacity );
    }

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
    return memcpy( malloc( V->item_size ), 
        (char*)V->base + ( V->item_size * index ), V->item_size );
}

void* find( Vector* V, cmp lt, void* target ) {
    unsigned int min = 0;
    unsigned int max = V->size;

    while( max >= min ) {
        unsigned int mid = min + ( ( max - min ) / 2 );
        if( lt( &((char*)V->base)[ mid * V->item_size ], target ) )
            min = mid + 1;
        else if( lt( target, &((char*)V->base)[ mid * V->item_size ] ) )
            max = mid - 1;
        else
            return &( (char*)V->base )[ mid * V->item_size ];
    }
    return NULL;
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

    // Moves the right part of the original vector, making a hole in the middle
    memcpy( (char*)base + ( pos + ins->size ) * size,
            (char*)orig->base + ( pos * size ), ( orig->size - pos ) * size );

    // Place the new vector in between
    memmove( (char*)base + ( pos * size ), ins->base, ins->size * size );

    free( orig->base );
    orig->base = base;
    orig->capacity = new_capacity;
    orig->size = orig->size + ins->size;
}
