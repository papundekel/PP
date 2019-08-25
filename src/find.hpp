#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"
#include "equals.hpp"
#include "move_.hpp"

template <typename R, typename P>
requires AND<range_type<R>, callable_r<P, bool, range_base<R>>>::v
auto find(R r, P&& p)
{
	for (; r && !p(*r); ++r);
	
	return r;
}

template <typename R, typename P>
requires AND<range_type<R>, equatable_with<P, range_base<R>>>::v
auto find(R r, const P& p)
{
	for (; r && p != *r; ++r);
	
	return r;
}