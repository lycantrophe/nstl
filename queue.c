#include "queue.h"

static move( Queue* Q, unsigned long first ) {
    memmove( Q->V.base, Q->first, first - ( unsigned long ) Q->V.base );
    Q->V.size -= first;
    Q->first = Q->V.base;
}

void enqueue( Queue* Q, void* item ) {
    unsigned long first = ( Q->first - Q->V.base ) / Q->V.item_size;
    unsigned long thresh = 2 * ( Q->V.capacity / Q->V.item_size ) / 3;
    unsigned long lthresh = ( Q->V.capacity / Q->V.item_size ) - thresh;

    if( Q->V.size == Q->V.capacity / Q->V.item_size && first >= thresh ) {
        move( Q, first );
        first = ( Q->first - Q->V.base ) / Q->V.item_size;
    }
    if( Q->V.size - first <= thresh / 2) {
        if( first >= thresh ) {
            move( Q, first );
            first = ( Q->first - Q->V.base ) / Q->V.item_size;
        }
        else
          Q->V.base = realloc( Q->V.base, Q->V.capacity /= 2);
    }
    if( first >= lthresh ) {
        move( Q, first );
    }

    push( &Q->V, item );
}
