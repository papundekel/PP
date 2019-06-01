#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "range.hpp"

template <typename it, typename it_end>
bool in_bounds(it i, range<it, it_end> c)
{
	if constexpr (is_iterator_ra<it> && is_iterator_ra<it_end>)
	{
		return i >= c.begin && i < c.end;
	}
	else
	{
		for (; c.begin != c.end && c.begin != i; ++c.begin);
		return c.begin != c.end;
	}
}