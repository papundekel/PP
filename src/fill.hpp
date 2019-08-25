#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename R, typename T = range_base<R>>
requires range_type<R>::v && assignable_to<T, range_base<R>>::v
void fill(R r, const T& value = T())
{
	for (; r; ++r)
		*r = value;
}