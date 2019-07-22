#pragma once
#include "range.hpp"
#include "construct.hpp"

template <range_t R, typename ...Args>
void u_fill(R r, Args&&... args)
{
	for (; r; ++r)
		construct(r.begin, forward<Args>(args)...);
}