#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename it, assignable_to<base_type<it>> T = base_type<it>>
void fill(range<it> r, const T& value = T())
{
	for (; r.begin != r.end; ++r.begin)
		*r.begin = value;
}