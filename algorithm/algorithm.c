#include "../nstl.h"
#include "algorithm.h"

void* binary_search( void* A, size_t typesize, unsigned int low, unsigned int high, void* target, cmp lt ) {
    unsigned int min = low;
    unsigned int max = high;

    while( max >= min ) {
        unsigned int mid = min + ( ( max - min ) / 2 );
        /* if A[ mid ] < target */
        if( lt( __at( A, mid, typesize ), target )
            min = mid + 1;
        /* if target < A[ mid ] */
        else if( lt( target, __at( A, mid, typesize ) )
            max = mid - 1;
        /* target == A[ mid ] */
        else
            return __at( A, mid, typesize );
    }
    return NULL;
}
