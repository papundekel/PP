#pragma once
#include "is_iterator.hpp"
#include "is_arithmetic.hpp"
#include "destroy_at.hpp"

template <typename it>
enable_if<is_iterator<it>,
void> destroy_n(it begin, size_t count)
{
	if constexpr (!is_arithmetic<it>)
		for (size_t i = 0; i != count; ++i, ++begin)
			destroy_at(begin);
}