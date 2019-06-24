#pragma once
#include "range.hpp"
#include "remove_cv.hpp"

template <range_t R, typename T = remove_cv<base_type<R>>>
T accumulate(R r, T init = T())
{
	for (; r.begin != r.end; ++r.begin)
		init += *r.begin;
	return init;
}