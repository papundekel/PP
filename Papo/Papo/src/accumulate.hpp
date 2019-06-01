#pragma once
#include "range.hpp"
#include "remove_cv.hpp"
#include "base_type.hpp"
template <typename it, typename it_end, typename T = remove_cv<base_type<it>>>
T accumulate(range<it, it_end> r, T init_value = T())
{
	for (; r.begin != r.end; ++r.begin)
		init_value += *r.begin;
	return init_value;
}