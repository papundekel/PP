#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "construct.hpp"

template <typename R, typename G>
requires range_type<R>::v && callable_r<G, range_base<R>>::v
void u_generate(R r, G g)
{
	for (; r; ++r)
		construct(+r, g());
}