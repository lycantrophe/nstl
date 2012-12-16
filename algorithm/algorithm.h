#ifndef ALGORITHM_H
#define ALGORITHM_H

typedef unsigned short (*cmp)(void*,void*);

/* Binary search the array, looking for the target element. Takes a function
 * pointer to a comparison function that should return positive if the first
 * argument is less than the second argument.
 */
extern void* binary_search( void* A, size_t typesize, unsigned int low, unsigned int high, void* target, cmp lt);

#endif //ALGORITHM_H
