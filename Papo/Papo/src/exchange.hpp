#pragma once
#include "move.hpp"
#include "forward.hpp"

template <typename T, typename U>
T exchange(T& object, U&& value)
{
	T old = move(object);
	object = forward<U>(value);
	return old;
}