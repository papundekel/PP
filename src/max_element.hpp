#pragma once
#include "range.hpp"

template <typename it>
it max_element(range<it> r)
{
	if (r.begin == r.end)
		return r.end;
	auto max = r.begin;
	while (++r.begin != r.end)
		if (*max < *r.begin)
			max = r.begin;
	return max;
}