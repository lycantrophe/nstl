#ifndef NSTL_H
#define NSTL_H

/*
 * This file defines common types such as void array index
 */

typedef unsigned short (*cmp)(void*,void*);
typedef void (*destructor)(void*);

typedef struct {
    destructor key;
    destructor payload;
} destroy_associative;

#endif //NSTL_H
