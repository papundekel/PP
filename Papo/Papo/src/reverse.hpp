#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "it_swap.hpp"

template <typename it>
enable_if<is_iterator<it>,
void> reverse(it begin, it end)
{
	for (; begin != end && begin != --end; ++begin)
		it_swap(begin, end);
}