#pragma once
#include "find.hpp"
#include "move_.hpp"

template <range_t R>
inline bool any_of(R r, auto&& p)
{
	return !find(r, move(p)).empty();
}