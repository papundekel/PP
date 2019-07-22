#pragma once
#include "movable.hpp"
#include "assignable.hpp"
#include "const_t.hpp"
#include "move.hpp"

template <movable T>
requires !const_t<T> && assignable_to<T&&, T>
void swap(T& first, T& second)
{
	T temp = move(first);
	first = move(second);
	second = move(temp);
}