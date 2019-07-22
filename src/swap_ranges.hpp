#pragma once
#include "it_swap.hpp"

template <Range First, Range Second>
void swap_ranges(First first, Second second)
{
	for (; first && second; ++first, ++second)
		it_swap(first.begin, second.begin);
}