#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "constructible_template.hpp"

template <typename R, typename F>
requires (range_type<R>::v  || constructible_template<range, R>::v) && callable<F, range_base<R>>::v
auto apply(const R& x, F f)
{
	if constexpr (range_type<R>::v)
	{
		auto r = x;
		for (; r; ++r)
			f(*r);
		return r;
	}
	else
		return apply(range(x), f);
}