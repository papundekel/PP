#pragma once
#include "range.hpp"
#include "construct.hpp"

template <range_t R, typename ...Args>
void u_fill(R r, Args&&... args)
{
	for (; r.begin != r.end; ++r.begin)
		construct(r.begin, forward<Args>(args)...);
}