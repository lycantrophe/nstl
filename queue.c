#include "queue.h"

static int move( Queue* Q, unsigned long first ) {
    memmove( Q->V.base, Q->first,
            first - ( unsigned long ) Q->V.base * Q->V.item_size );
    Q->V.size -= first;
    Q->first = Q->V.base;
    return ( Q->first - Q->V.base ) / Q->V.item_size;
}

void enqueue( Queue* Q, void* item ) {
    unsigned long first, type_cap, thresh, lthresh;

    first = ( Q->first - Q->V.base ) / Q->V.item_size;
    type_cap = Q->V.capacity / Q->V.item_size;
    thresh = 2 * type_cap / 3;
    lthresh = type_cap / 10;

    if( Q->V.size == tyoe_cap && first >= thresh )
        first = move( Q, first );
    if( Q->V.size - first <= thresh / 2) {
        if( first >= thresh )
            first = move( Q, first );
        else
          Q->V.base = realloc( Q->V.base, Q->V.capacity /= 2);
    }
    if( first >= lthresh )
        move( Q, first );

    push( &Q->V, item );
}
