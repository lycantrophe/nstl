#include "queue.h"

void enqueue( Queue* Q, void* item ) {
    unsigned int first = (Q->V.base - Q->first) / Q->V.item_size;
    if(first >= 2 * (Q->V.capacity / Q->V.item_size) / 3) {
        memmove(Q->V.base, Q->first, Q->V.base - first);
        Q->V.base = realloc(Q->V.base, Q->V.capacity);
    }
    push( &Q->V, item );
}
