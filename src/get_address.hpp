#pragma once
#include "iterator.hpp"
#include <memory>

template <iterator_c I>
auto get_address(I i)
{
	return std::addressof(*i);
}