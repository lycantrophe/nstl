#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

typedef List Circular;

extern Circular* circular( void* payload );
extern Circular* link( Circular* list, void* payload );
extern void* unlink( Circular* );
extern Circular* follow( Circular* );
extern Circular* reverse( Circular* );
extern void* get_payload( Circular* );

#endif //CIRCULAR_H
