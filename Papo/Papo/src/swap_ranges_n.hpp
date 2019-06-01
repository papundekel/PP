#pragma once
template <typename it1, typename it2>
void swap_ranges_n(it1 firstBegin, size_t count, it2 secondBegin)
{
	for (size_t i = 0; i != count; ++i, ++firstBegin, ++secondBegin)
		it_swap(firstBegin, secondBegin);
}