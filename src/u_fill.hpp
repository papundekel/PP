#pragma once
#include "range.hpp"
#include "construct.hpp"

template <typename R, typename ...Args>
requires range_type(type<R>{})
void u_fill(R r, Args&&... args)
{
	for (; r; ++r)
		construct(+r, forward<Args>(args)...);
}