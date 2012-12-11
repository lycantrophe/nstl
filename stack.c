#include "stack.h"
#include "vector.h"

void* pop( Vector* V ) {
    return (char*)V->base + ( --( V->size ) * V->item_size );
}
