#ifndef HEAP_H
#define HEAP_H
#include "nstl-types.h"
#include "vector.h"

/*
 * Converts a vector into a heap. Destroys its previous order.
 *
 * Requres a less than (<) comparison function for max heap. Give it a gt (>)
 * for min-heap.
 */
extern void heap( Vector*, cmp );

/*
 * Pushes the new item onto the heap. 
 */
extern void heappush( Vector*, cmp, void* item );

/*
 * Pops and returns the top item off the heap. Allocated on the heap, so call
 * free() afterwards.
 */
extern void* heappop( Vector*, cmp );

#endif //HEAP_H
