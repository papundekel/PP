#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename R, typename T = decl_type<range_base(type<R>{})>>
requires range_type(type<R>{}) && assignable(type<T>{}, range_base(type<R>{}))
void fill(R r, const T& value = T())
{
	for (; r; ++r)
		*r = value;
}