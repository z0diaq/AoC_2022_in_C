#include "array.h"
#include "utils.h"

#include <memory.h>
#include <stdio.h>

struct Array*
ArrayCreate( size_t _initialCapacity, size_t _elementSize )
{
	struct Array* result = malloc( sizeof( struct Array ) );
	ASSURE( result );

	result->memory = calloc( _initialCapacity, _elementSize );
	ASSURE( result->memory );

	result->size = 0;
	result->capacity = _initialCapacity;
	result->elementSize = _elementSize;

	return result;
}

void
ArrayDestroy( struct Array** _array )
{
	if( *_array )
	{
		RELEASE( ( *_array )->memory );
		( *_array )->capacity = ( *_array )->size = 0;
		RELEASE( *_array );
	}
}

void
ArrayPush( struct Array* _array, void* _value )
{
	if( _array->size == _array->capacity )
	{
		const size_t newCapacity = max_size_t( ( _array->capacity * 3 ) >> 1, 8 );// make ~1,5x bigger but at least 8
		void* newValues = realloc( _array->memory, newCapacity * _array->elementSize );
		ASSURE( newValues );
		_array->memory = newValues;
		memset(
			_array->memory + _array->size * _array->elementSize,
			0,
			( newCapacity - _array->size ) * _array->elementSize );
		_array->capacity = newCapacity;
	}

	memcpy(
		_array->memory + _array->size * _array->elementSize,
		_value,
		_array->elementSize );
	++_array->size;
}

void *
ArrayGet( struct Array* _array, size_t _index )
{
	ASSURE( _array );
	ASSURE( _index < _array->size );

	return _array->memory + _index * _array->elementSize;
}

size_t
ArraySize( struct Array* _array )
{
	ASSURE( _array );
	return _array->size;
}

size_t
ArrayCapacity( struct Array* _array )
{
	ASSURE( _array );
	return _array->capacity;
}

void
ArraySort( struct Array* _array, cmpFunction fun )
{
	ASSURE( _array );
	qsort( _array->memory, _array->size, _array->elementSize, fun );
}
