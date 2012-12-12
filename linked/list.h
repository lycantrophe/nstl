#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct List {
    void* payload;
    struct List* next;
    struct List* prev;
} List;

extern List* link( List*, void* );
extern void* unlink( List* );


#endif //LINKEDLIST_H
