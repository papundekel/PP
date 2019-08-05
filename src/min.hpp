#pragma once
#include "ordered.hpp"
template <ordered_c T>
constexpr const T& min(const T& a, const T& b)
{
	return a < b ? a : b;
}