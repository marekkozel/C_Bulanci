#include "dynamic_array.h"

void dynarray_init(dynarray *array, int initial_capacity)
{
    array->items = (array_type *)malloc(sizeof(array_type) * initial_capacity);
    array->size = 0;
    array->capacity = initial_capacity;
    memset(array->items, 0, sizeof(array_type) * initial_capacity);
}

void dynarray_push(dynarray *array, array_type item)
{
    if (array->capacity == array->size)
    {
        int new_capacity = array->capacity * 2;
        array_type *memory = (array_type *)malloc(sizeof(array_type) * new_capacity);
        memcpy(memory, array->items, array->size * sizeof(array_type));
        free(array->items);

        array->items = memory;
        array->capacity = new_capacity;
    }

    array->items[array->size] = item;
    array->size += 1;
}

array_type dynarray_get(dynarray *array, int id)
{
    return array->items[id];
}

void dynarray_remove(dynarray *array, array_type item)
{
    for (int i = 0; i < array->size; i++)
    {
        if (array->items[i] == item)
        {
            free(item);

            for (int j = i + 1; j < array->size; j++)
            {
                array->items[j - 1] = array->items[j];
            }
            array->size--;

            i--;
        }
    }
}

void dynarray_free(dynarray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        free(array->items[i]);
    }
    free(array->items);
}
