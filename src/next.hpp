#pragma once
#include "iterator.hpp"

template <typename I>
requires iterator<I>
auto next(I i)
{
	return ++i;
}