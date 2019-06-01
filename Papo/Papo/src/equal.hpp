#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "range.hpp"

template <typename it1, typename it1_end, typename it2>
enable_if<is_iterator<it2>,
bool> equal(range<it1> first, it2 second_begin)
{
	for (; first.begin != first.end && *first.begin == *second_begin; ++first.begin, ++second_begin);
	return first.begin == first.end;
}

template <typename it1, typename it1_end, typename it2, typename it2_end>
bool equal(range<it1, it1_end> first, range<it2, it2_end> second)
{
	for (; (first.begin != first.end || second.begin != second.end) && *first.begin == *second.begin; ++first.begin, ++second.begin);
	return  first.begin == first.end && second.begin == second.end;
}