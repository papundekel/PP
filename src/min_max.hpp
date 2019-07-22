#pragma once
#include "pair.hpp"

template <typename T>
constexpr pair<T, T> min_max(const T& a, const T& b)
{
	return a < b ? { a, b } : { b, a };
}