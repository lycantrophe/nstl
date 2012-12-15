#include <stdlib.h>
#include <string.h>
#include "../nstl-types.h"
#include "sort.h"

static inline void* __at( void* A, unsigned int index, size_t typesize ) {
    return (char*)A + ( index * typesize );
}

void insertion_sort( void* A, size_t typesize, unsigned int first, unsigned int last, cmp lt ) {
    for( unsigned int i = first + 1; i < last; ++i ) {
        /* Remember the current item and its index */
        void* item = memcpy( malloc( typesize ),
                __at( A, i, typesize ), typesize );
        unsigned int hole = i;

        while( hole > 0 && lt( item, __at( A, hole - 1, typesize ) ) ) {
            /* A[hole] = A[hole-1] */
            memmove( __at( A, hole, typesize ),
                    __at( A, hole - 1, typesize ), typesize );
            --hole;
        }

        /* A[hole] = item */
        memmove( __at( A, hole, typesize ), item, typesize );
    }
}
