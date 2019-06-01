#pragma once
#include "iterator.hpp"

template <iterator I>
auto next(I i)
{
	return ++i;
}