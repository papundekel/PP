#pragma once
#include "iterator.hpp"
#include <memory>

template <typename I>
requires iterator(type<I>{})
auto get_address(I i)
{
	return std::addressof(*i);
}