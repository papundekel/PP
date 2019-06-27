#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"
#include "equals.hpp"
#include "move_.hpp"

template <range_t R, typename P>
auto find(R r, P&& p)
{
	if constexpr (bool(callable_r<P, bool, range_base<R>>))
		for (; r && !p(*r); ++r);
	else if constexpr (bool(equatable_with<P, range_base<R>>))
		for (; r && p != *r; ++r);
	
	return r;
}