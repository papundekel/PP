#pragma once
#include "enable_if.hpp"
#include "range.hpp"
#include "equal.hpp"

template <Range R, Range R_sub>
auto find_sub(R r, R_sub r_sub)
{
	for (; r && !equal(r_sub, r); ++r);
	return r.begin;
}