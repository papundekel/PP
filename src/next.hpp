#pragma once
#include "iterator.hpp"

template <typename I>
requires iterator<I>::v
auto next(I i)
{
	return ++i;
}