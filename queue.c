#include <assert.h>
#include "queue.h"
#include "vector.h"

Queue* queue( size_t typesize, unsigned int icap ) {
    Queue* Q = malloc( sizeof( Queue ) );
    Q->V.base = malloc( icap * typesize );
    Q->V.size = 0;
    Q->V.item_size = typesize;
    Q->V.capacity = icap;
    Q->first = Q->V.base;
    return Q;
}

static unsigned int move( Queue* Q ) {
    Vector* V = &Q->V;
    unsigned int offset = ( (char*)Q->first - (char*)V->base ) / V->item_size;

    size_t bytes = ( V->size - offset ) * V->item_size;
    Q->first = memmove( V->base, Q->first, bytes );

    V->size -= offset;
    return 0;
}

void enqueue( Queue* Q, void* item ) {
    Vector* V = &Q->V;
    unsigned int first = ( (char*)Q->first - (char*)V->base ) / V->item_size;
    unsigned int type_cap = V->capacity / V->item_size;
    unsigned int move_threshold = type_cap / 10;

    if( V->size == type_cap && first >= move_threshold )
        first = move( Q );

    size_t used = ( V->size - first ) * V->item_size;
    if( V->capacity - used > 2*V->capacity / 3 ) {
        if( first >= move_threshold )
            first = move( Q );
        else
            V->base = realloc( V->base, V->capacity /= 2 );
    }

    push( V, item );
    Q->first = (char*)V->base + ( first * V->item_size );
}

void* dequeue( Queue* Q ) {
    assert( Q->V.size );

    void* retptr = Q->first;
    Q->first = (char*)Q->first + Q->V.item_size;

    return memcpy( malloc( Q->V.item_size ), retptr, Q->V.item_size );
}
