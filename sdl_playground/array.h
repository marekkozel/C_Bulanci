#include <stdlib.h>

typedef struct {
    void ** data;
    int capacity;
    int count;
    int element_size;
} Array;


void array_init( Array * self, int capacity, int element_size );
void * array_push( Array * self );
void * array_get( Array * self, int pos );
void array_free( Array * self );