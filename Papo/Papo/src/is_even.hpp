#pragma once
#include "is_integral.hpp"
template <typename T>
bool is_even(T value)
{
	static_assert(is_integral<T>, "is_even: value must be integral");
	return value % 2 == 0;
}