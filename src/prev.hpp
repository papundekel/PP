#pragma once
#include "iterator_bi.hpp"

template <typename I>
requires iterator_bi(type<I>{})
auto prev(I i)
{
	return --i;
}