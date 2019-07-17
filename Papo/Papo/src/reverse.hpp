#pragma once
#include "range.hpp"
#include "it_swap.hpp"

template <Range R>
void reverse(R r)
{
	for (; r && r.begin != --r.end; ++r)
		it_swap(r.begin, r.end);
}