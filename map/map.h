#ifndef MAP_H
#define MAP_H

/*
 * Defines the interface for Map types. 
 */

typedef struct {
    void (*insert)( void*, void*, void* );
    void* (*remove)( void*, void* );
    void* (*get)( void*, void* );
} Map;

#endif //MAP_H
