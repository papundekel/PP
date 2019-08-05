#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <range_c R, assignable_to_c<range_base<R>> T = range_base<R>>
void fill(R r, const T& value = T())
{
	for (; r; ++r)
		*r = value;
}