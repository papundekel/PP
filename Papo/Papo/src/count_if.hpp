#pragma once
#include "range.hpp"
#include "callable.hpp"

template <range_t R, callable_r<bool, range_base<R>> P>
size_t count_if(R r, P p)
{
	size_t cnt = 0;
	for (; r; ++r)
		if (p(*r))
			++cnt;
	return cnt;
}