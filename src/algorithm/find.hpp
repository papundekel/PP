#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"

template <typename R, typename P>
requires range_type<R> && callable_r<P, bool, range_base<R>>
auto find(R r, P&& p)
{
	for (; r && !p(*r); ++r);
	return r;
}

template <typename R, typename P>
requires range_type<R> && equatable<P, range_base<R>>
auto find(R r, const P& p)
{
	return find(r, [p](auto& x){ return p == x; });
}