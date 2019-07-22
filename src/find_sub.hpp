#pragma once
#include "enable_if.hpp"
#include "range.hpp"
#include "equal.hpp"

template <range_t R, range_t R_sub>
auto find_sub(R r, R_sub r_sub)
{
	for (; r && !equal(r_sub, r); ++r);
	return r.begin;
}