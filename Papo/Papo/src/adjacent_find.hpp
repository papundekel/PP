#pragma once
#include "enable_if.hpp"
#include "range.hpp"
template <typename it, typename it_end>
it adjacent_find(range<it, it_end> r)
{
	it next = r.begin;
	for (; ++next != r.end; ++r.begin)
		if (*r.begin == *next)
			return r.begin;
	return r.end;
}