#pragma once
#include "construct.hpp"
#include "range.hpp"

template <range_t R, typename ...Args>
void u_fill(R dest, Args&&... args)
{
	for (; dest.begin != dest.end; ++dest.begin)
		construct(dest.begin, forward<Args>(args)...);
}