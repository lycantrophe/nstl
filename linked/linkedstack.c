#include "linkedstack.h"

Linkedstack* linkedstack( void ) {
    return calloc( 1, sizeof( Linkedstack ) );
}

void linkedpush( Linkedstack* S, void* payload ) {
    S->head = link( S->head, payload);
    if(!S->size) S->tail = S->head;
    ++S->size;
}

void* linkedpop( Linkedstack* S ) {
    assert( S->size );

    --S->size;

    List* head = S->head;
    S->head = head->prev;
    return unlink( head );
}

void* linkedpeek( Linkedstack* S ) {
    assert( S->head );
    return S->head->payload;
}
