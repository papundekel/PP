#pragma once
#include "iterator.hpp"
#include <memory>

template <iterator it>
auto get_address(it i)
{
	return std::addressof(*i);
}