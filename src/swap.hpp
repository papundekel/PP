#pragma once
#include "constructible.hpp"
#include "assignable.hpp"
#include "const_type.hpp"
#include "move.hpp"

template <typename T>
//requires AND<NOT<const_type<T>>, constructible<T, T&&>, assignable<T&&, T>>::v
void swap(T& first, T& second)
{
	T temp = move(first);
	first = move(second);
	second = move(temp);
}