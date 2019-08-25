#pragma once
#include "range.hpp"
#include "next.hpp"

template <range_c R>
auto adjacent_find(R r)
{
	if (r)
		for (auto i = next(r.begin); i != r.end; ++r, ++i)
			if (*r == *i)
				return r;
	return r;
}