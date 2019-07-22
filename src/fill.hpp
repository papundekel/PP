#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename it, assignable_to<base<it>> T = base<it>>
void fill(range<it> r, const T& value = T())
{
	for (; r.begin != r.end; ++r.begin)
		*r.begin = value;
}