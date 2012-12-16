#include "linkedstack.h"

Linkedstack* linkedstack( void ) {
    Linkedstack *S;
    return S = calloc( 1, sizeof(Linkedstack) );
}

void linkedstack_push( Linkedstack* S, void* payload ) {
    S->head = link( S->head, payload);

    if(!S->size)
      S->tail = S->head;

    ++S->size;
}

void* linkedstack_pop( Linkedstack* S ) {
    assert( S->size );

    void* retptr;
    --S->size;

    List* newhead = S->head->prev;
    retptr = unlink( S->head );
    S->head = newhead;

    return retptr;
}
