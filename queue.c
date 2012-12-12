#include "queue.h"

void enqueue( Queue* Q, void* item ) {
    unsigned long first = ( Q->V.base - Q->first ) / Q->V.item_size;

    if( first >= 2 * ( Q->V.capacity / Q->V.item_size ) / 3 )
        memmove( Q->V.base, Q->first, first - ( unsigned long ) Q->V.base );
    if( Q->V.capacity - ( Q->V.size * Q->V.item_size ) > 2 * Q->V.capacity / 3)
        Q->V.base = realloc(Q->V.base, Q->V.capacity /= 2 );

    push( &Q->V, item );
}
