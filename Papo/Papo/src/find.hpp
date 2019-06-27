#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "equatable.hpp"
#include "equals.hpp"

template <range_t R, callable_r<bool, range_base<R>> P>
auto find(R r, P&& p)
{
	for (; r && !p(*r); ++r);
	return r;
}