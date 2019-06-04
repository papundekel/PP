#pragma once
#include "range.hpp"
#include "callable.hpp"
template <range_t R, callable_r<bool, typename R::base_t> test>
auto find_if(R r, F f)
{
	for (; r.begin != r.end && !f(*r.begin); ++r.begin);
	return r.begin;
}