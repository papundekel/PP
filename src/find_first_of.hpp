#pragma once
#include "find.hpp"

template <range_t R, range_t R_sub>
auto find_first_of(R r, R_sub r_sub)
{
	for (; r && find(r_sub, *r).empty(); ++r);
	return r;
}