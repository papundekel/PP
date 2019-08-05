#pragma once
#include "iterator.hpp"

template <iterator_c I>
auto next(I i)
{
	return ++i;
}