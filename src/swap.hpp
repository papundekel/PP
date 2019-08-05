#pragma once
#include "constructible.hpp"
#include "assignable.hpp"
#include "const.hpp"
#include "move.hpp"

template <typename T>
requires !const_c<T> && constructible_c<T, T&&> && assignable_to_c<T&&, T>
void swap(T& first, T& second)
{
	T temp = move(first);
	first = move(second);
	second = move(temp);
}