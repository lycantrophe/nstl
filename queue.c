#include <assert.h>
#include "queue.h"
#include "vector.h"

Queue* queue( size_t typesize, unsigned int icap ) {
    Queue* Q = malloc( sizeof( Queue ) );
    Q->V.base = malloc( icap * typesize );
    Q->V.size = 0;
    Q->V.item_size = typesize;
    Q->V.capacity = icap;
    Q->items = Q->V.size = 0;
    Q->V.item_size = typesize;
    Q->V.capacity = icap * typesize;
    Q->first = Q->V.base;
    return Q;
}

static inline void move( Queue* Q ) {
    Vector* V = &Q->V;

    size_t bytes = Q->items * V->item_size;
    Q->first = memmove( V->base, Q->first, bytes );
    V->size -= Q->items;
}

void enqueue( Queue* Q, void* item ) {
    Vector* V = &Q->V;
    unsigned int type_cap = V->capacity / V->item_size;

    /* If more than 1/4 (left of the first item) is free: move */
    if( V->size == type_cap && V->size - Q->items > type_cap / 4 ) 
        move( Q );

    size_t offset = (char*)Q->first - (char*)V->base;
    push( V, item );
    ++Q->items;
    Q->first = (char*)V->base + offset;
}

void* dequeue( Queue* Q ) {
    assert( Q->items );

    void* retptr = Q->first;
    Q->first = (char*)Q->first + Q->V.item_size;
    --Q->items;
    return memcpy( malloc( Q->V.item_size ), retptr, Q->V.item_size );
}
