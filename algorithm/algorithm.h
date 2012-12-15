#ifndef ALGORITHM_H
#define ALGORITHM_H

typedef unsigned short (*cmp)(void*,void*);

extern void* binary_search( void* A, size_t typesize, unsigned int low, unsigned int high, void* target, cmp lt);

#endif //ALGORITHM_H
