#ifndef SORT_H
#define SORT_H

#include "../nstl-types.h"

/*
 * Plain insertion sort between high and low
 */
extern void insertion_sort( void *A, size_t, unsigned int, unsigned int, cmp );

/*
 * An improvement on plain insertion sort. 
 */
extern void shell_sort( void *A, size_t, unsigned int, unsigned int, cmp );

/*
 * Randomized quicksort that switches to insertion sort for <= 32 elements
 */
extern void quick_sort( void *A, size_t, int, int, cmp );

#endif //SORT_H
