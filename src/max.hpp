#pragma once
#include "ordered.hpp"
template <ordered_c T>
constexpr const T& max(const T& a, const T& b)
{
	return a < b ? b : a;
}