#pragma once

#include <stddef.h>

//very basic dynamic array - functionality will be expanded when needed

struct Array
{
	char*  memory;
	size_t size;
	size_t capacity;
	size_t elementSize;
};

struct Array* ArrayCreate( size_t _initialCapacity, size_t _elementSize );
void ArrayDestroy( struct Array** _array );

void ArrayPush( struct Array* _array, void* _value );
void* ArrayGet( struct Array* _array, size_t _index );
size_t ArraySize( struct Array* _array );
size_t ArrayCapacity( struct Array* _array );

typedef int( *cmpFunction )( const void*, const void* );
void ArraySort( struct Array* _array, cmpFunction fun );
