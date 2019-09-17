#pragma once
#include "iterator.hpp"

template <typename I>
requires iterator(type<I>{})
auto next(I i)
{
	return ++i;
}