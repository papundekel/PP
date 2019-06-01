#pragma once
#include "is_reference.hpp"

template <typename it, typename T>
void fill_n(it begin, size_t count, const T& value)
{
	static_assert(is_convertible<T, base_type<it>>, "fill_n: value is not compatible with iterator");
	for (size_t i = 0; i != count; ++i, ++begin)
		*begin = value;
}