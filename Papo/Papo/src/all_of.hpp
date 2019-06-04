#pragma once
#include "find_if_not.hpp"
template <range_t R, typename F>
bool all_of(R r, F f)
{
	return find_if_not(r, f) == r.end;
}