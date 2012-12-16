#include <stdlib.h>
#include <string.h>
#include "../nstl-types.h"
#include "sort.h"

/*
 * Notice that sorts does NOT assert boundries. This is by design - a higher
 * first than last shall return the same array
 */

static inline void* __at( void* A, unsigned int index, size_t typesize ) {
    return (char*)A + ( index * typesize );
}

static inline void __move( void* A, unsigned int to, unsigned int from, size_t typesize ) {
    memmove( __at( A, to, typesize ), __at( A, from, typesize ), typesize );
}

static inline void* __copy( void* item, void* A, unsigned int index, size_t typesize ) {
    return memcpy( item, __at( A, index, typesize ), typesize );
}

void insertion_sort( void* A, size_t typesize, unsigned int first, unsigned int last, cmp lt ) {
    void* item = malloc( typesize );
    for( unsigned int i = first + 1; i < last; ++i ) {
        /* Remember the current item and its index */
        item = __copy( item, A, i, typesize );
        unsigned int hole = i;

        while( hole > 0 && lt( item, __at( A, hole - 1, typesize ) ) ) {
            /* A[hole] = A[hole-1] */
            __move( A, hole, hole - 1, typesize );
            --hole;
        }

        /* A[hole] = item */
        memmove( __at( A, hole, typesize ), item, typesize );
    }
    free( item );
}

void shell_sort( void* A, size_t typesize, unsigned int first, unsigned int last, cmp lt ) {
    unsigned int gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
    unsigned int *gap = gaps;

    for( unsigned int i = 0; i < 8 && *gap > first; ++i, ++gap )
        insertion_sort( A, typesize, *gap, last, lt );
}
