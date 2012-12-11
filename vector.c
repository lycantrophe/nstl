#include <stdlib.h>
#include <string.h>
#include "vector.h"

Vector* vector( size_t typesize, size_t icap ) {
    Vector* V = malloc( sizeof( Vector ) );
    V->base = malloc( icap * typesize );
    V->capacity = icap;
    V->size = 0;
    V->item_size = typesize;
    return V;
}

void push( Vector* V, void* item ) {
    if( V->size == V->capacity ) {
        V->capacity *= 2;
        V->base = realloc( V->base, V->item_size * V->capacity );
    }

    void* dst = ((char*)V->base) + V->item_size * V->size;
    memcpy( dst, item, V->item_size );
    ++V->size;
}

void* find( Vector* V, cmp lt, void* target ) {
    unsigned int min = 0;
    unsigned int max = V->size;

    while( max >= min ) {
        unsigned int mid = min + ( ( max - min ) / 2 );
        if( lt( &((char*)V->base)[ mid * V->item_size ], target ) )
            min = mid + 1;
        else if( lt( target, &((char*)V->base)[ mid * V->item_size ] ) )
            max = mid - 1;
        else
            return &( (char*)V->base )[ mid * V->item_size ];
    }
    return NULL;
}
