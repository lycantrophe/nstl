#include "stack.h"
#include "vector.h"

void* pop( Vector* V ) {
    return (char*)V->base + ( --( V->capacity ) * V->item_size );
}
