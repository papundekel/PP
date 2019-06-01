#pragma once
#include "find_if.hpp"
template <typename it, typename test>
bool any_of(range<it> r, test t)
{
	static_assert(is_callable<bool, test, base_type<it>>, "any_of: t must be callable as \"bool(base_type<it>)\"");
	return find_if(r.begin, r.end, t) != r.end;
}