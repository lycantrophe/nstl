#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct List {
    void* payload;
    struct List* next;
    struct List* prev;
} List;

/*
 * Creates a new node with the passed payload and appends it onto the given
 * list. If list is NULL both next and prev in the returned node is set to
 * NULL.
 */
extern List* link( List* list, void* payload );

/*
 * Unlinks the given List item from its list. Binds its next/prev together
 */
extern void* unlink( List* );


#endif //LINKEDLIST_H
