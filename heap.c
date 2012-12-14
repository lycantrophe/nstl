#include <string.h>
#include <assert.h>
#include "heap.h"
#include "vector.h"

/* Calculate parent index */
static inline unsigned int __heap_parent( unsigned int i ) {
    return i / 2;
}

/* Calculate left child index */
static inline unsigned int __heap_left( unsigned int i ) {
    return i * 2;
}

/* Calculate right child index */
static inline unsigned int __heap_right( unsigned int i ) {
    return ( i * 2 ) + 1;
}

inline static void swap( void* l, void* r, size_t size ) {
    void* tmp = memcpy( malloc( size ), l, size );
    memcpy( l, r, size );
    memcpy( r, tmp, size );
    free( tmp );
}

/* Comments wil assume max-heap, that is a less-than (<) compare */
/* Situation is reversed for min-heap */
static void heapify( Vector* V, cmp compare, unsigned int i ) {
    void* parent = at( V, i );
    void* largest = parent;
    unsigned int largest_index = i;
    unsigned int child = __heap_left( i );

    /* Work with parent or left child? */
    if( child < V->size ) {
        void* left = at( V, child );
        if( compare( parent, left ) ) {
            largest = left;
            largest_index = child;
        }
    }

    /* Work with right child? */
    if( ++child < V->size ) {
        void* right = at( V, child );
        if( compare( largest, right ) ) {
            largest = right;
            largest_index = child;
        }
    }

    if( largest != parent ) {
        swap( parent, largest, V->item_size );
        heapify( V, compare, largest_index );
    }
}

void heap( Vector* V, cmp compare ) {
    int floor = V->size / 2;
    for( int i = floor; i >= 0; --i )
        heapify( V, compare, i );
}

static void heap_increase_key( Vector* V, cmp compare, unsigned int i, void* key ) {
    assert( !compare( key, at( V, i ) ) );

    memcpy( ((char*)V->base) + ( i * V->item_size ), key, V->item_size );
    /* V[ parent(i) ] < V[ i ] */
    while( i > 0 && compare( at( V, __heap_parent( i ) ), at( V, i ) ) ) {
        swap( at( V, __heap_parent( i ) ), at( V, i ), V->item_size );
        i = __heap_parent( i );
    }
}

void heappush( Vector* V, cmp compare, void* item ) {
    push( V, item );
    heap_increase_key( V, compare, V->size - 1, item );
}

void* heappop( Vector* V, cmp compare ) {
    void* max = get( V, 0 );
    /* Move all memory left and reduce heap size */
    memmove( V->base, (char*)V->base + ( ( --V->size ) * V->item_size ),
            V->item_size );

    heapify( V, compare, 0 );
    return max;
}
