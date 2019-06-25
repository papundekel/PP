#pragma once
#include "range.hpp"
#include "callable.hpp"
template <range_t R, callable_r<bool, range_base<R>> F>
auto find_if_not(R r, F&& f)
{
	for (; r.begin != r.end && f(*r.begin); ++r.begin);
	return r.begin;
}