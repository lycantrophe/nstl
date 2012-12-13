#include "list.h"
#include "circular.h"

Circular* circular( void* payload ) {
    Circular* circ = malloc( sizeof( Circular ) );
    circ->next = circ;
    circ->prev = circ;
    circ->payload = payload;
    return circ;
}
