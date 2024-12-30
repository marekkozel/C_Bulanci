#pragma once

#include <SDL2/SDL.h>
#include "Config/sdl.h"
#include <stdlib.h>
#include <string.h>

typedef void *array_type;

typedef struct
{
    array_type *items;
    int size;
    int capacity;
} dynarray;

void dynarray_init(dynarray *array, int initial_capacity);

array_type dynarray_get(dynarray *array, int id);

void dynarray_push(dynarray *array, array_type item);

void dynarray_remove(dynarray *array, array_type item);

void dynarray_free(dynarray *array);