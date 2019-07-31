#pragma once
#include "movable.hpp"
#include "assignable.hpp"
#include "const.hpp"
#include "move.hpp"

template <movable T>
requires !Const<T> && assignable_to<T&&, T>
void swap(T& first, T& second)
{
	T temp = move(first);
	first = move(second);
	second = move(temp);
}