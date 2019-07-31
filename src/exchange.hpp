#pragma once
#include "move.hpp"
#include "forward.hpp"
#include "not.hpp"

template <non<is_const> T, typename U>
T exchange(T& object, U&& value)
{
	T old = move(object);
	object = forward<U>(value);
	return old;
}