#ifndef RB_MAP_H
#define RB_MAP_H
#include "map.h"
#include "../tree/redblack.h"

static const Map rb_map = {
    (void (*)(void*,void*,void*))&rb_insert_unique,
    (void* (*)(void*,void*))&rb_remove,
    (void* (*)(void*,void*))&rb_get
};

#endif //RB_MAP_H
