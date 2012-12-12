#include <stdlib.h>
#include <assert.h>
#include "deque.h"
#include "link.h"

Deque* deque( void ) {
    Deque* D = malloc( sizeof( Deque ) );
    D->head = D->tail = NULL;
    D->size = 0;
    return D;
}

void deenqueue( Deque* D, void* payload ) {
    D->tail = link( D->tail, payload );
    if( !D->head ) D->head = D->tail;
    ++D->size;
}

void* dedequeue( Deque* D ) {
    assert( D->size );
    --D->size;
    List* head = D->head;
    D->head = head->next;
    return unlink( head );
}
