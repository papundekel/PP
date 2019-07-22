#pragma once
#include <cstddef>

template <size_t size1, size_t size2>
constexpr size_t fit_count(size_t count)
{
	return ((count * size2 - 1 + size1) & (~size1 + 1)) / size1;
}

template <typename T, typename U>
constexpr size_t fit_count(size_t count)
{
	return ((count * sizeof(U) - 1 + sizeof(T)) & (~sizeof(T) + 1)) / sizeof(T);
}