#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "construct.hpp"

template <range_t R, callable_r<typename R::base_t> G>
void u_generate(R r, G g)
{
	for (; r.begin != r.end; ++r.begin)
		construct(r.begin, g());
}