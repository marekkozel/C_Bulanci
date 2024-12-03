#include "array.h"

void array_init( Array * self, int capacity, int element_size ) {
    self->data = malloc( capacity * sizeof( void * ) );
    self->capacity = capacity;
    self->count = 0;
    self->element_size = element_size;
}

void * array_push( Array * self ) {
    void * value = NULL;
    value = malloc( self->element_size );

    if ( self->count == self->capacity ) {
        self->capacity = self->capacity * 2;
        self->data = realloc( self->data, sizeof( void * ) * self->capacity );
    }

    self->data[ self->count ] = value;
    self->count += 1;

    return value;
}

void * array_get( Array * self, int pos ) {
    return self->data[ pos ];
}

void array_free( Array * self ) {
    for ( int i = 0; i < self->count; i++ ) {
        free( self->data[ i ] );
        self->data[ i ] = NULL;
    }
    free( self->data );
    self->data = NULL;
}