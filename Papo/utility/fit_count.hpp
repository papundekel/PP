#pragma once
#include <cstddef>

template <size_t size1, size_t size2>
constexpr size_t fit_count(size_t count)
{
	return 1 + ((count * size2 - 1) / size1);
}

template <typename T, typename U>
constexpr size_t fit_count(size_t count)
{
	return fit_count<sizeof(T), sizeof(U)>(count);
}