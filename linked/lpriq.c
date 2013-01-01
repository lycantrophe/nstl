#include "list.h"
#include "linkedstack.h"
#include "deque.h"

List* backtrack( List* );

struct Lpriqueue {
    unsigned int size;
    List* head;
    List* tail;
};

static inline struct Lpriqueue* Lpriqueue( void ) {
    struct Lpriqueue* D = malloc( sizeof( struct Lpriqueue ) );
    D->head = D->tail = NULL;
    D->size = 0;
    return D;
}

/* Pushes onto the tail */
static inline void lpush( struct Lpriqueue* L, void* payload ) {
    L->tail = link( L->tail, payload );
    /* Set head pointer as well if this is the first (and only) element */
    if( !L->head ) L->head = L->tail;
    ++L->size;
}

static inline void* lpop( struct Lpriqueue* L ) {
    assert( L->size );

    --L->size;

    List* tail = L->tail;
    L->tail = reverse( tail );
    return unlink( tail );
}

/*
 * Stack
 */

Linkedstack* linkedstack( void ) {
    return Lpriqueue();
}

void linkedpush( Linkedstack* S, void* payload ) {
    lpush( S, payload );
}

void* linkedpop( Linkedstack* S ) {
    return lpop( S );
}

void* linkedpeek( Linkedstack* S ) {
    assert( S->head );
    return get_payload( S->head );
}

/*
 * Double ended queue
 */

Deque* deque( void ) {
    return Lpriqueue();
}

void deenqueue( Deque* D, void* payload ) {
    lpush( D, payload );
}

void* dedequeue( Deque* D ) {
    assert( D->size );
    --D->size;
    List* head = D->head;
    D->head = follow( head );
    return unlink( head );
}

void* depop( Deque* D ) {
    return lpop( D );
}
