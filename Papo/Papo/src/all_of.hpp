#pragma once
#include "find_if_not.hpp"
template <typename it, typename it_end, typename test>
bool all_of(range<it, it_end> r, test t)
{
	static_assert(is_callable<bool, test, base_type<it>>, "all_of: t must be callable as \"bool(base_type<it>)\"");
	return find_if_not(r, t) == r.end;
}