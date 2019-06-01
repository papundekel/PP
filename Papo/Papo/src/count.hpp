#pragma once
#include "range.hpp"
template <typename it, typename it_end, typename T>
size_t count(range<it, it_end> r, const T& value)
{
	size_t result = 0;
	for (; r.begin != r.end; ++r.begin)
		if (*r.begin == value)
			++result;
	return result;
}