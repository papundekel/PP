#pragma once
#include "enable_if.hpp"
#include "is_const.hpp"
#include "move.hpp"
template <typename T>
void swap(T& first, T& second)
{
	static_assert(!is_const<T>, "swap: T is const");

	T temp = move(first);
	first = move(second);
	second = move(temp);
}