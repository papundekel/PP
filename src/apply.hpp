#pragma once
#include "range.hpp"
#include "callable.hpp"

template <typename R, typename F>
requires range_type<R>::v && callable<F, range_base<R>>::v
auto apply(R r, F f)
{
	for (; r; ++r)
		f(*r);
	return r;
}