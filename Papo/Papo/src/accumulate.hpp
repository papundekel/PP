#pragma once
#include "range.hpp"
#include "remove_cv.hpp"

template <range_t R, typename T = remove_cv<range_base<R>>>
T accumulate(R r, T init = T())
{
	for (; !r.empty(); ++r)
		init += *r;
	return init;
}