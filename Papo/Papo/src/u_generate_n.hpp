#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "is_function.hpp"
#include "construct.hpp"

template <typename it, typename generator>
enable_if<is_iterator<it> && is_function<generator>,
void> u_generate_n(it begin, size_t count, generator g)
{
	for (size_t i = 0; i != count; ++i, ++begin)
		construct(begin, g());
}