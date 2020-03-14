#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename R, typename T = range_base<R>>
requires range_type<R> && assignable<T, range_base<R>>
void fill(R r, const T& value = T())
{
	for (; r; ++r)
		*r = value;
}