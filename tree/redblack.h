#ifndef REDBLACK_H
#define REDBLACK_H

#include "../nstl-types.h"

typedef enum { RED, BLACK } RBCOLOR;

/*
 * A node with a payload pointer. Can be used for regular trees and map
 * lookups. Can be used for a key/value structure
 */

typedef struct Rbnode {
    RBCOLOR color;
    void* key;
    void* payload;
    struct Rbnode* left;
    struct Rbnode* right;
    struct Rbnode* parent;
} Rbnode;

typedef struct {
    Rbnode* root;
    cmp lt;
} Red_black;

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

#endif //REDBLACK_H
