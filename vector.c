#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"
#include "stack.h"
#include "queue.h"

#define EXTRA_ALLOC_LIMIT 32

struct Vector {
    void* base;
    unsigned int size;
    size_t capacity;
    size_t item_size;
};

struct Vector* __initialize_vector( struct Vector* V, size_t typesize, unsigned int icap ) {
    V->base = malloc( icap * typesize );
    V->capacity = icap * typesize;
    V->size = 0;
    V->item_size = typesize;
    return V;
}

struct Vector* vector( size_t typesize, unsigned int icap ) {
    return __initialize_vector( malloc( sizeof( struct Vector ) ), typesize, icap );
}

void push( struct Vector* V, void* item ) {
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

void* at( struct Vector* V, unsigned int index ) {
    assert( index <= V->size );
    return (char*)V->base + ( V->item_size * index );
}

void* get( struct Vector* V, unsigned int index ) {
    assert( index <= V->size );
    return memcpy( malloc( V->item_size ), at( V, index ), V->item_size );
}

void insert_vector( struct Vector* orig, struct Vector* ins, unsigned int pos ) {
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

unsigned int vector_size( struct Vector* V ) {
    return V->size;
}

void* destroy_vector( struct Vector* V, void (*F)( void* ) ) {
    void* ptr = V->base;
    if( F ) 
        for( unsigned int i = 0; i < V->size; ++i, ptr = (char*)ptr + V->item_size )
            F( ptr );

    free( V->base );
    free( V );
    return NULL;
}

/*
 * STACK
 */

void* pop( Vector* V ) {
    /* Frees some memory if less than 2/3
     * of the allocated space is being used 
     */
    if( V->capacity - ( V->size * V->item_size ) > 2*V->capacity / 3 ) {
        V->capacity /= 2;
        V->base = realloc( V->base, V->capacity );
    }

    void* retptr = (char*)V->base + ( --( V->size ) * V->item_size );
    return memcpy( malloc( V->item_size ), retptr, V->item_size );
}

void* peek( Vector* V ) {
    return at( V, V->size - 1 );
}

/*
 * QUEUE
 */

struct Queue {
    Vector* V;
    void* first;
    unsigned int items;
};

Queue* queue( size_t typesize, unsigned int icap ) {
    Queue* Q = malloc( sizeof( Queue ) );
    Q->V = malloc( sizeof( Vector ) );
    __initialize_vector( Q->V, typesize, icap );
    Q->items = Q->V->size; // = 0;
    Q->first = Q->V->base;
    return Q;
}

Queue* vtoq( Vector* V ) {
    Queue* Q = malloc( sizeof( Queue ) );
    Q->V = V;
    Q->items = V->size;
    Q->first = V->base;
    return Q;
}

static inline void move( Queue* Q ) {
    Vector* V = Q->V;

    size_t bytes = Q->items * V->item_size;
    Q->first = memmove( V->base, Q->first, bytes );
    V->size -= Q->items;
}

void enqueue( Queue* Q, void* item ) {
    Vector* V = Q->V;
    unsigned int type_cap = V->capacity / V->item_size;

    /* If more than 1/4 (left of the first item) is free: move */
    if( V->size == type_cap && V->size - Q->items > type_cap / 4 ) 
        move( Q );

    /* Calculate first/base offset in case push causes a realloc */
    size_t offset = (char*)Q->first - (char*)V->base;
    push( V, item );
    ++Q->items;
    Q->first = (char*)V->base + offset;
}

void* dequeue( Queue* Q ) {
    assert( Q->items );

    void* retptr = Q->first;
    Q->first = (char*)Q->first + Q->V->item_size;
    --Q->items;
    return memcpy( malloc( Q->V->item_size ), retptr, Q->V->item_size );
}

void* destroy_queue( struct Queue* Q, void (*F)( void* ) ) {
    destroy_vector( Q->V, F );
    free( Q );
    return NULL;
}

/*
 * Privates
 */

size_t __vector_item_size( Vector* V ) {
    return V->item_size;
}

size_t __queue_item_size( Queue* Q ) {
    return Q->V->item_size;
}

