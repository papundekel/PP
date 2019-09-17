#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"

template <typename R, typename P>
requires range_type(type<R>{}) && callable_r(type<P>{}, type<bool>{}, range_base(type<R>{}))
auto find(R r, P&& p)
{
	for (; r && !p(*r); ++r);
	return r;
}

template <typename R, typename P>
requires range_type(type<R>{}) && equatable(type<P>{}, range_base(type<R>{}))
auto find(R r, const P& p)
{
	for (; r && p != *r; ++r);
	return r;
}