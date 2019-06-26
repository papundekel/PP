#pragma once
#include "range.hpp"
#include "callable.hpp"

template <range_t R, callable<range_base<R>> F>
auto apply(R r, F f)
{
	for (; r; ++r)
		f(*r);
	return r;
}