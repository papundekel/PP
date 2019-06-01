#pragma once
#include "ordered.hpp"
template <ordered T>
constexpr const T& min(const T& a, const T& b)
{
	return a < b ? a : b;
}