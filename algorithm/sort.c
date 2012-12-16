#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../nstl-types.h"
#include "sort.h"

/*
 * Notice that sorts does NOT assert boundries. This is by design - a higher
 * first than last shall return the same array
 */

static unsigned int seeded = 0;

static unsigned int random( unsigned int from, unsigned int to ) {
    if( !seeded ) srand( time( NULL ) );
    seeded = 1;
    return ( rand() % ( to - from ) ) + from;
}

static inline void* __at( void* A, unsigned int index, size_t typesize ) {
    return (char*)A + ( index * typesize );
}

static inline void __move( void* A, unsigned int to, unsigned int from, size_t typesize ) {
    memmove( __at( A, to, typesize ), __at( A, from, typesize ), typesize );
}

/* Copies A[index] into item */
static inline void* __copy( void* item, void* A, unsigned int index, size_t typesize ) {
    return memcpy( item, __at( A, index, typesize ), typesize );
}

static inline void __swap( void* A, unsigned int left, unsigned int right, size_t typesize ) {
    void* tmp = __copy( malloc( typesize ), A, right, typesize );
    __move( A, right, left, typesize );
    memcpy( __at( A, left, typesize ), tmp, typesize );
    free( tmp );
}

static inline unsigned int __partition( void* A, size_t typesize, unsigned int left, unsigned int right, unsigned int pivot, cmp lt ) {
    /* Move pivot to end */
    void* pivot_val = __at( A, pivot, typesize );
    __swap( A, pivot, right, typesize );
    pivot_val = __at( A, right, typesize );

    unsigned int index = left;

    for( unsigned int i = left; i < right; ++i ) {
        /* if A[ i ] < pivot */
        if( lt( __at( A, i, typesize ), pivot_val ) )
            __swap( A, i, index++, typesize );
    }

    __swap( A, index, right, typesize );
    return index;
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

void quick_sort( void* A, size_t typesize, int first, int last, cmp lt ) {
    /* if list has >= 2 items */
    if( first >= last )
        return;

    /* For small arrays: use insertion sort */
    if( last - first < 33 ) {
        insertion_sort( A, typesize, first, last, lt );
        return;
    }

    int pivot = random( first, last );
    int new_pivot = __partition( A, typesize, first, last, pivot, lt );
    quick_sort( A, typesize, first, new_pivot - 1, lt );
    quick_sort( A, typesize, new_pivot + 1, last, lt );
}
