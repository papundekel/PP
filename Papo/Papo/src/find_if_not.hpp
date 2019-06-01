#pragma once
#include "range.hpp"
#include "is_callable.hpp"
#include "base_type.hpp"
template <typename it, typename test>
it find_if_not(range<it> r, test t)
{
	static_assert(is_callable<bool, test, base_type<it>>, "find_if_not: t must be callable as \"bool(base_type<it>)\"");
	for (; r.begin != r.end && t(*r.begin); ++r.begin);
	return r.begin;
}