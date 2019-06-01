#pragma once
#include "range.hpp"
#include "move.hpp"
template <typename it1, typename it2>
it2 move_backward(it1 srcBegin, it1 srcEnd, it2 destEnd)
{
	while (srcEnd != srcBegin)
		*(--destEnd) = move(*(--srcEnd));
	return destEnd;
}
template <typename it1, typename it1_end, typename it2, typename it2_end>
it2 move_backward(range<it1, it1_end> src, range<it2, it2_end> dest)
{
	while (src.end != src.begin)
		*(--dest.end) = move(*(--src.end));
	return dest.end;
}