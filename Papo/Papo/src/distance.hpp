#pragma once
#include "range.hpp" 
#include "iterator_ra.hpp"

template <typename it, typename it_end>
size_t distance(range<it, it_end> r)
{
	if constexpr (iterator_ra<it> && iterator_ra<it_end>)
		return r.end - r.begin;
	else
	{
		size_t hops = 0;
		for (; r.begin != r.end; ++hops, ++r.begin);
		return hops;
	}
}