#ifndef CIRCULAR_H
#define CIRCULAR_H

typedef List Circular;

extern Circular* circular( void* payload );
extern Circular* link( Circular* list, void* payload );
extern void* unlink( Circular* );

#endif //CIRCULAR_H
