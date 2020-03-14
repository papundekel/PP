#pragma once
#include "find.hpp"
#include "move_.hpp"

template <range_c R>
bool any_of(R r, auto&& p)
{
	return !find(r, move(p)).empty();
}