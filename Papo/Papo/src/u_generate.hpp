#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "construct.hpp"

template <range_t R, callable_r<base_type<R>> G>
void u_generate(R r, G g)
{
	for (; !r.empty; ++r)
		construct(r.begin, g());
}