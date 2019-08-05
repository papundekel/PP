#pragma once
#include "move.hpp"
#include "forward.hpp"
#include "not.hpp"

template <not_c<const_s> T, typename U>
T exchange(T& object, U&& value)
{
	T old = move(object);
	object = forward<U>(value);
	return old;
}