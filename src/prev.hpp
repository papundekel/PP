#pragma once
#include "iterator_bi.hpp"

template <iterator_bi_c I>
auto prev(I i)
{
	return --i;
}