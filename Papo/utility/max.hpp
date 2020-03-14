#pragma once
#include "ordered.hpp"
template <typename T>
requires ordered<T>
constexpr const T& max(const T& a, const T& b)
{
	return a < b ? b : a;
}