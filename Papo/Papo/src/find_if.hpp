#pragma once
#include "range.hpp"
#include "is_callable.hpp"
#include "base_type.hpp"
template <typename it, typename it_end, typename test>
it find_if(range<it, it_end> r, test t)
{
	static_assert(is_callable<bool, test, base_type<it>>, "find_if: t must be callable as \"bool(base_type<it>)\"");
	for (; r.begin != r.end && !t(*r.begin); ++r.begin);
	return r.begin;
}