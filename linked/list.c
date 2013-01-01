#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "circular.h"

struct List {
    void* payload;
    struct List* next;
    struct List* prev;
};

struct List* link( struct List* node, void* payload ) {
    struct List* link = calloc( 1, sizeof( List ) );
    link->payload = payload;

    if( !node ) return link;

    link->next = node->next;
    link->prev = node;
    node->next = link;

    return link;
}

void* unlink( struct List* node ) {
    assert( node );
    void* payload = node->payload;

    if( node->prev )
        node->prev->next = node->next;

    if( node->next )
        node->next->prev = node->prev;

    free( node );
    return payload;
}

struct List* follow( struct List* list ) {
    assert( list );
    return list->next;
}

struct List* reverse( struct List* L ) {
    assert( L );
    return L->prev;
}

void* get_payload( struct List* list ) {
    assert( list );
    return list->payload;
}

/* Creates a regular list element, but binds next/prev to itself.
 * Link handles the circular property automatically
 */
Circular* circular( void* payload ) {
    Circular* circ = malloc( sizeof( Circular ) );
    circ->next = circ;
    circ->prev = circ;
    circ->payload = payload;
    return circ;
}
