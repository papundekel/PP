#pragma once
#include "range.hpp"
#include "remove_cv.hpp"
#include "base_type.hpp"
template <typename it, typename T = remove_cv<base_type<it>>>
T iota(range<it> r, T value = T())
{
	for (; r.begin != r.end; ++r.begin, ++value)
		*r.begin = value;
	return value;
}