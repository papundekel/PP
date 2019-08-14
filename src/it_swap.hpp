#pragma once
#include "enable_if.hpp"
#include "iterator.hpp"
#include "is_same.hpp"
#include "base_type.hpp"
#include "swap.hpp"

template <iterator First, iterator Second>
void it_swap(First first, Second second)
{
	swap(*first, *second);
}