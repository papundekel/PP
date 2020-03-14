#pragma once
#include "iterator_bi.hpp"

template <typename I>
requires iterator_bi<I>
auto prev(I i)
{
	return --i;
}