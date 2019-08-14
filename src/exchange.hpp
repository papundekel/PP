#pragma once
#include "move.hpp"
#include "forward.hpp"
#include "non.hpp"

template <typename T, typename U>
requires non<const_type, T>::v
T exchange(T& object, U&& value)
{
	T old = move(object);
	object = forward<U>(value);
	return old;
}