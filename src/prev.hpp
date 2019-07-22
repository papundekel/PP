#pragma once
#include "iterator_bi.hpp"

template <iterator_bi I>
auto prev(I i)
{
	return --i;
}