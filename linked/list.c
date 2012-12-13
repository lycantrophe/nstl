#include <stdlib.h>
#include <assert.h>
#include "list.h"

List* link( List* node, void* payload ) {
    List* link = calloc( 1, sizeof( List ) );
    link->payload = payload;

    if( !node ) return link;

    link->next = node->next;
    link->prev = node;
    node->next = link;

    return link;
}

void* unlink( List* node ) {
    assert( node );
    void* payload = node->payload;

    if( node->prev )
        node->prev->next = node->next;

    if( node->next )
        node->next->prev = node->prev;

    free( node );
    return payload;
}
