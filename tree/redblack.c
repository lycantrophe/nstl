#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../nstl-types.h"
#include "redblack.h"

typedef enum { RED, BLACK } RBCOLOR;

typedef struct Rbnode {
    RBCOLOR color;
    void* key;
    void* payload;
    struct Rbnode* left;
    struct Rbnode* right;
    struct Rbnode* parent;
} Rbnode;

struct Red_black {
    Rbnode* root;
    cmp lt;
};

static inline Rbnode* __tree_min( Rbnode* x ) {
    while( x->left )
        x = x->left;
    return x;
}

static inline Rbnode* __tree_max( Rbnode* x ) {
    while( x->right )
        x = x->right;
    return x;
}

/*
 * Rotate a tree to the left.
 */
static Rbnode* __left_rotate( Rbnode* x ) {
    if( !x->right ) return NULL;

    Rbnode* y = x->right;
    x->right = y->left;

    if( y->left )
        y->left->parent = x;

    y->left = x;
    return y;
}

/*
 * Rotate a subtree to the right
 */
static Rbnode* __right_rotate( Rbnode* x ) {
    if( !x->left ) return NULL;

    Rbnode* y = x->left;
    x->left = y->right;

    if( y->right )
        y->right->parent = x;

    y->right = x;
    return y;
}

/*
 * Common procedure for all rotations. Boolean parameter left determines
 * rotation direction.
 */
static inline void __rotate( Red_black* rbt, Rbnode* x, unsigned short left ) {
    Rbnode* y = left ? __left_rotate( x ) : __right_rotate( x );
    if( !y ) return;

    y->parent = x->parent;

    if( !x->parent ) rbt->root = y;
    else if( x == x->parent->left ) x->parent->left = y;
    else x->parent->right = y;

    x->parent = y;
}

/* eq (==) comparison */
static inline unsigned int __eq( void* lhs, void* rhs, cmp lt ) {
    return !( lt( lhs, rhs ) || lt( rhs, lhs ) );
}

/*
 * Rotates and fixes the tree according to maintain the rb-tree properties if
 * the newly inserted key violates its properties.
 */
static void __rb_insert_fixup( Red_black* rbt, Rbnode* z ) {
    while( z->parent && z->parent->color == RED ) {

        /* Boolean parameter that mirrors the prodcedure and gives its
         * left/right rotations
         */
        unsigned short left = ( z->parent == z->parent->parent->left );

        Rbnode* y = z->parent->parent;
        y = left ? y->right : y->left;
        /* if y is NULL it is also black */
        if( y && y->color == RED ) {
            z->parent->color = y->color = BLACK;
            z = z->parent->parent;
            z->color = RED;
        }
        else if( z == ( left ? z->parent->right : z->parent->left ) )
            __rotate( rbt, z = z->parent, left );
        else {
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            __rotate( rbt, z->parent->parent, !left );
        }
    }

    rbt->root->color = BLACK;
}

static void __rb_remove_fixup( Red_black* rbt, Rbnode* x ) {
    while( x != rbt->root && x != NULL && x->color == RED ) {

        unsigned short left = ( x == x->parent->left );

        Rbnode* y = x->parent;
        y = left ? y->right : y->left;

        if( y && y->color == RED ) {
            y->color = BLACK;
            x->parent->color = RED;
            __rotate( rbt, x->parent, left );
            y = x->parent->right;
        }

        if( y ->left->color == BLACK && y->right->color == BLACK ) {
            y->color = RED;
            x = x->parent;
        }

        else {
            if( y->right->color == BLACK ) {
                y->left->color = BLACK;
                y->color = RED;
                __rotate( rbt, y, !left );
            }
            y->color = x->parent->color;
            x->parent->color = y->right->color = BLACK;
            __rotate( rbt, x, left );
            x = rbt->root;
        }
    }

    if( x )
        x->color = BLACK;
}

static Rbnode* __get( Red_black* rbt, void* key ) {
    Rbnode* x = rbt->root;

    if( !x )
        return NULL;

    while( x ) {
        if( rbt->lt( key, x->key ) )
            x = x->left;
        else if( rbt->lt( x->key, key ) )
            x = x->right;
        else
            return x;
    }

    return NULL;
}

static inline Rbnode* __lookup_collision( Rbnode* x, void* key, cmp lt ) {
    Rbnode* y = NULL;
    while( x ) {
        y = x;
        if( lt( key, x->key ) )
            x = x->left;
        else 
            x = x->right;
    }
    return y;
}

/* Looks up and checks for collision */
static inline Rbnode* __lookup_noncollision( Rbnode* x, void* key, cmp lt ) {
    Rbnode* y = NULL;
    while( x ) {
        y = x;
        if( lt( key, x->key ) )
            x = x->left;
        else if( lt( x->key, key ) )
            x = x->right;
        else
            return NULL;
    }
    return y;
}

/* Returns true if key is inserted */
static inline Rbnode* __lookup( Rbnode* x, void* key, cmp lt, unsigned short unique ) {
    return unique ? __lookup_noncollision( x, key, lt ) :
        __lookup_collision( x, key, lt );
}

static inline Rbnode* __sibling( Rbnode* x ) {
    return x == x->parent->left ? x->parent->left : x->parent->right;
}

static inline Rbnode* rbnode( void* key, void* payload ) {
    Rbnode* node = malloc( sizeof( Rbnode ) );
    node->parent = node->left = node->right = NULL;
    node->key = key;
    node->payload = payload;
    node->color = RED;
    return node;
}

static inline void __insert( Red_black* rbt, void* key, void* payload, unsigned short unique ) {
    Rbnode* z = rbnode( key, payload );
    Rbnode* y = __lookup( rbt->root, key, rbt->lt, unique );

    /* return if unique and nothing is inserted */
    if( !y && unique )
        return;

    z->parent = y;

    if( y == NULL )
        rbt->root = z;
    else if( rbt->lt( key, y->key ) )
        y->left = z;
    else
        y->right = z;

    __rb_insert_fixup( rbt, z );
}

static inline Rbnode* __tree_successor( Rbnode* x ) {
    if( x->left )
        return __tree_min( x->right );

    Rbnode* y = x->parent;

    /* Keep moving up the tree */
    while( y && x == y->right ) {
        x = y;
        y = y->parent;
    }

    return y;
}

static inline void __delete( Red_black* rbt, Rbnode* z ) {
    Rbnode* x = NULL;
    Rbnode* y = NULL;

    if( z->left == NULL || z->right == NULL )
        y = z;
    else 
        y = __tree_successor( z );

    if( y->left )
        x = y->left;
    else
        x = y->right;

    if( !y->parent ) 
        x->parent = y->parent;

    if( !y->parent )
        rbt->root = x;
    else if( y->parent->left && y == y->parent->left )
        y->parent->left = x;
    else if( y->parent->right && y == y->parent->right )
        y->parent->right = x;

    /* transfer satellite data */
    if( y != z ) {
        z->key = y->key;
        z->payload = y->payload;
    }

    if( y->color == BLACK )
        __rb_remove_fixup( rbt, x );

    free( y );
}

Red_black* redblack( cmp lt ) {
    Red_black* rb = malloc( sizeof( Red_black ) );
    rb->lt = lt;
    rb->root = NULL;
    return rb;
}


void rb_insert( Red_black* rbt, void* key, void* payload ) {
    __insert( rbt, key, payload, 0 );
}

void rb_insert_unique( Red_black* rbt, void* key, void* payload ) {
    __insert( rbt, key, payload, 1 );
}

void* rb_remove( Red_black* rbt, void* key ) {
    Rbnode* node = __get( rbt, key );
    if( !node )
        return NULL;

    void* payload = node->payload;
    __delete( rbt, node );
    return payload;
}

void* rb_get( Red_black* rbt, void* key ) {
    Rbnode* node = __get( rbt, key );
    return node ? node->payload : NULL;
}

