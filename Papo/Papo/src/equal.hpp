#pragma once
#include "enable_if.hpp"
#include "iterator.hpp"
#include "range.hpp"

template <range_t R, typename it2>
bool equal(R first, it2 second_begin)
{
	for (; first.begin != first.end && *first.begin == *second_begin; ++first.begin, ++second_begin);
	return first.begin == first.end;
}

template <range_t R1, range_t R2>
bool equal(R1 first, R2 second)
{
	for (; (first.begin != first.end || second.begin != second.end) && *first.begin == *second.begin; ++first.begin, ++second.begin);
	return  first.begin == first.end && second.begin == second.end;
}