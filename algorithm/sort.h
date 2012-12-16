#ifndef SORT_H
#define SORT_H

#include "../nstl-types.h"

/*
 * Sets threshold when sorts switch from their regular sort to insertion sort.
 * Defaults to 32 elements.
 */

extern void set_insertion_threshold( unsigned int threshold );

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
