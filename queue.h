#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>
#include "vector.h"

typedef struct {
    Vector V;
    void* first;
} Queue;

#endif
