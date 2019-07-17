#pragma once
#include "range.hpp"
#include "callable.hpp"

template <Range R, callable<range_base<R>> F>
auto apply(R r, F f)
{
	for (; r; ++r)
		f(*r);
	return r;
}