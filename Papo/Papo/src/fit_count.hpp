#pragma once
#include <cstddef>
template <size_t size1, size_t size2>
constexpr size_t fit_count(size_t count)
{
	return ((count * size2 - 1 + size1) & (~size1 + 1)) / size1;
}