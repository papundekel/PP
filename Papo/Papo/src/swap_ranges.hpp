#pragma once
#include "it_swap.hpp"

template <range_t First, range_t Second>
void swap_ranges(First first, Second second)
{
	for (; !first.empty() && !second.empty(); ++first, ++second)
		it_swap(first.begin, second.begin);
}