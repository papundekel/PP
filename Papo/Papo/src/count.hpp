#pragma once
#include "range.hpp"
#include "equatable.hpp"

template <range_t R, equatable_with<range_base<R>> T>
size_t count(R r, const T& value)
{
	size_t result = 0;
	for (; r; ++r)
		if (*r == value)
			++result;
	return result;
}