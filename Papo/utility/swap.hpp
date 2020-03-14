#pragma once
#include "constructible.hpp"
#include "assignable.hpp"
#include "type/const.hpp"
#include "move_.hpp"

template <typename T>
requires !const_type(t<T>) && constructible<T, T&&> && assignable<T&&, T>
void swap(T& first, T& second)
{
	auto temp = move(first);
	first = move(second);
	second = move(temp);
}