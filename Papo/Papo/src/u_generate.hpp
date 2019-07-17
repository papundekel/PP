#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "construct.hpp"

template <Range R, callable_r<range_base<R>> G>
void u_generate(R r, G g)
{
	for (; r; ++r)
		construct(r.begin, g());
}