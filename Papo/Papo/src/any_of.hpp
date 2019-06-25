#pragma once
#include "find_if.hpp"
template <range_t R, typename F>
bool any_of(R r, F f)
{
	return find_if(r, f) != r.end;
}