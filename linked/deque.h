#ifndef DEQUE_H
#define DEQUE_H

#include "list.h"

typedef struct {
    unsigned int size;
    List* head;
    List* tail;
} Deque;

extern Deque* deque( void );
extern void deenqueue( Deque*, void* );
extern void* dedequeue( Deque* );

#endif //DEQUE_H
