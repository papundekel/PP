#pragma once
#include "constructible.hpp"
#include "assignable.hpp"
#include "const_type.hpp"
#include "move.hpp"

template <typename T>
requires !const_type<T>::v && constructible<T, T&&>::v && assignable_to<T&&, T>::v
void swap(T& first, T& second)
{
	T temp = move(first);
	first = move(second);
	second = move(temp);
}