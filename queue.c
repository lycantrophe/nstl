#include "queue.h"

void enqueue( Queue* Q, void* item ) {
    unsigned long first = ( Q->first - Q->V.base ) / Q->V.item_size;
    unsigned long thresh = 2 * ( Q->V.capacity / Q->V.item_size ) / 3;

    if( Q->V.size - first <= thresh && first >= thresh ) {
        memmove( Q->V.base, Q->first, first - ( unsigned long ) Q->V.base );
        Q->V.size -= first;
        Q->first = Q->V.base;

        if( Q->V.size <= thresh )
            Q->V.base = realloc( Q->V.base, Q->V.capacity /= 2 );
    }

    push( &Q->V, item );
}
