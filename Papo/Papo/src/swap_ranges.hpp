#pragma once
template <typename it1, typename it2>
void swap_ranges(it1 firstBegin, it1 firstEnd, it2 secondBegin)
{
	for (; firstBegin != firstEnd; ++firstBegin, ++secondBegin)
		it_swap(firstBegin, secondBegin);
}