#pragma once
#include "range.hpp"
#include "callable.hpp"

template <range_t R, callable_r<bool, range_base<R>> test>
auto find_if(R r, F f)
{
	for (; r && !f(*r); ++r);
	return r.begin;
}