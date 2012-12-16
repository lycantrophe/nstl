#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <stdlib.h>
#include <assert.h>
#include "linkpriqueue.h"

typedef Lpriqueue Linkedstack;

Linkedstack* linkedstack( void );
void linkedpush( Linkedstack*, void* );
void* linkedpop( Linkedstack* );

#endif //LINKEDSTACK_H
