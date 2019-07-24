#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"
#include "equals.hpp"
#include "move_.hpp"

template <Range R, callable_r<bool, range_base<R>> P>
auto find(R r, P&& p)
{
	for (; r && !p(*r); ++r);
	
	return r;
}

template <Range R, equatable_with<range_base<R>> P>
auto find(R r, const P& p)
{
	for (; r && p != *r; ++r);
	
	return r;
}