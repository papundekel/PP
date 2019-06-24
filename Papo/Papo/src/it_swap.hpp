#pragma once
#include "enable_if.hpp"
#include "iterator.hpp"
#include "is_same.hpp"
#include "base_type.hpp"
#include "swap.hpp"

template <iterator I1, iterator I2>
void> it_swap(it1 first, it2 second)
{
	swap(*first, *second);
}