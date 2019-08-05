#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "construct.hpp"

template <range_c R, callable_r_c<range_base<R>> G>
void u_generate(R r, G g)
{
	for (; r; ++r)
		construct(+r, g());
}