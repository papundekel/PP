#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "constructible_template.hpp"

template <typename R, typename F>
requires (range_type(type<R>{}) || constructible_template<range>(type<R>{})) && callable(type<F>{}, range_base(type<R>{}))
auto apply(const R& x, F f)
{
	if constexpr (range_type(type<R>{}))
	{
		auto r = x;
		for (; r; ++r)
			f(*r);
		return r;
	}
	else
		return apply(range(x), f);
}