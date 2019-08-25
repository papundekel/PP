#pragma once
#include "iterator.hpp"
#include <memory>

template <typename I>
requires iterator<I>::v
auto get_address(I i)
{
	return std::addressof(*i);
}