#include <stdlib.h>
#include "list.h"
#include "circular.h"

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
