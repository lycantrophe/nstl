#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "vector.h"

void* pop( Vector* V ) {
    /* Frees some memory if less than 2/3
     * of the allocated space is being used 
     */
    if( V->capacity - ( V->size * V->item_size ) > 2*V->capacity / 3 ) {
        V->capacity /= 2;
        V->base = realloc( V->base, V->capacity );
    }

    void* retptr = (char*)V->base + ( --( V->size ) * V->item_size );
    return memcpy( malloc( V->item_size ), retptr, V->item_size );
}
