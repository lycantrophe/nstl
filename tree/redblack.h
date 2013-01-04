#ifndef REDBLACK_H
#define REDBLACK_H

#include "../nstl-types.h"

#define destroy_rb(RB) destroy_rb1(RB)
#define destroy_rb(RB,D) destroy_rb2(RB,D)

/*
 * A node with a payload pointer. Can be used for regular trees and map
 * lookups. Can be used for a key/value structure
 */

struct Red_black;
typedef struct Red_black Red_black;

/*
 * Initialize a new red black tree and saves its comparator.
 */
extern Red_black* redblack( cmp lt );

/*
 * Inserts a new key into the tree 
 */
extern void rb_insert( Red_black*, void*, void* );

/*
 * Inserts a new key into the tree with an associated value. Maintains a
 * uniqueness property - any duplicate key will not be added to the tree.
 */
extern void rb_insert_unique( Red_black*, void*, void* );

/*
 *  Removes the approperiate node from the tree and returns its payload.
 *  Returns NULL if it is not in the tree.
 */
extern void* rb_remove( Red_black*, void* key );

/*
 * Returns the payload of the node with the given key. Returns NULL if key is
 * not in the tree.
 */
extern void* rb_get( Red_black*, void* key );

/*
 * Destroys the red-black tree and frees all its data. 
 * If destroy_associative is NULL, free is called at both key and element. If
 * either of the FPs are NULL then free will be called on their respective
 * objects. Otherwise the respective element will be given to the approperiate
 * destructor function. Returns NULL.
 */
extern void* destroy_rb( Red_black*, destroy_associative* );

#endif //REDBLACK_H
