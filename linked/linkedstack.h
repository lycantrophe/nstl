#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <stdlib.h>
#include <assert.h>
#include "linkpriqueue.h"

typedef Lpriqueue Linkedstack;

Linkedstack* linkedstack( void );
void linkedstack_push( Linkedstack*, void* );
void* linkedstack_pop( Linkedstack* );

#endif //LINKEDSTACK_H
