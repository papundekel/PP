#pragma once
#include "move.hpp"
#include "forward.hpp"

template <typename T, typename U>
requires !const_type(type<T>{})
T exchange(T& object, U&& value)
{
	T old = move(object);
	object = forward<U>(value);
	return old;
}