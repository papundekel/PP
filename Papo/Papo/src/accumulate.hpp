#pragma once
#include "range.hpp"
#include "remove_cv.hpp"

template <range_t R, typename T = remove_cv<range_base<R>>>
auto accumulate(R r, T init = T())
{
	for (; r; ++r)
		init += *r;
	return init;
}