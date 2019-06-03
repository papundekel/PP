#pragma once
#include "range.hpp"
#include "next.hpp"
template <range_t R>
auto adjacent_find(R r)
{
	if (!r.empty())
		for (auto i = next(r.begin); i != r.end; ++r.begin, ++i)
			if (*r.begin == *i)
				return r.begin;
	return r.end;
}