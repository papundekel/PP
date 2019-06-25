#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "it_swap.hpp"

template <range_t R>
void> reverse(R r)
{
	for (; r && r.begin != --r.end; ++r)
		it_swap(r.begin, r.end);
}