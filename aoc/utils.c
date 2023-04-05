#include "utils.h"

size_t min_size_t( size_t _lhs, size_t _rhs )
{
	return _lhs < _rhs ? _lhs : _rhs;
}

size_t max_size_t( size_t _lhs, size_t _rhs )
{
	return _lhs > _rhs ? _lhs : _rhs;
}
