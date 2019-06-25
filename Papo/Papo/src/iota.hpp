#pragma once
#include "range.hpp"
#include "remove_cv.hpp"

template <range_t R, typename T = remove_cv<range_base<R>>>
T iota(R r, T value = T())
{
	for (; r; ++r, ++value)
		*r = value;
	return value;
}