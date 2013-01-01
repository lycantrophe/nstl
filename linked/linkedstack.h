#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <stdlib.h>
#include <assert.h>

struct Lpriqueue;
typedef struct Lpriqueue Linkedstack;

Linkedstack* linkedstack( void );
void linkedpush( Linkedstack*, void* );
void* linkedpop( Linkedstack* );
void* linkedpeek( Linkedstack* );

#endif //LINKEDSTACK_H
