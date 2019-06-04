#pragma once
#include "find_if_not.hpp"
template <range_t R, callable_r<bool, typename R::base_t> F>
bool all_of(R r, F f)
{
	return find_if_not(r, f) == r.end;
}