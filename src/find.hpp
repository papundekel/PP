#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"
#include "equals.hpp"
#include "move_.hpp"

template <range_c R, callable_r_c<bool, range_base<R>> P>
auto find(R r, P&& p)
{
	for (; r && !p(*r); ++r);
	
	return r;
}

template <range_c R, equatable_with_c<range_base<R>> P>
auto find(R r, const P& p)
{
	for (; r && p != *r; ++r);
	
	return r;
}