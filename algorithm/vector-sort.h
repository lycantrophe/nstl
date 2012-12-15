#ifndef VECTOR_SORT_H
#define VECTOR_SORT_H

#include "../vector.h"
#include "sort.h"

#define insort( V, lt ) insertion_sort( V->base, V->item_size, 0, V->size, lt );

#endif //VECTOR_SORT_H
