#pragma once
#include "enable_if.hpp"
#include "const_t.hpp"
#include "move.hpp"

template <typename T>
requires !const_t<T>
void swap(T& first, T& second)
{
	T temp = move(first);
	first = move(second);
	second = move(temp);
}