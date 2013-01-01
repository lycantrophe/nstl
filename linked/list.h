#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct List;
typedef struct List List;

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

/*
 * Jumps to the next item in the linked list. Returns
 * NULL if there is no further to go. (i.e. is tail)
 */
extern List* follow( List* list );

/*
 * Jumps to the previous item in the linked list. Returns
 * NULL if it is head.
 */
extern List* reverse( List* list );

/*
 * Returns the payload of the given list item.
 */
extern void* get_payload( List* list );


#endif //LINKEDLIST_H
