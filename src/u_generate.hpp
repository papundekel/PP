#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "construct.hpp"

template <typename R, typename G>
requires range_type(type<R>{}) && callable_r(type<G>{}, range_base(type<R>{}))
void u_generate(R r, G g)
{
	for (; r; ++r)
		construct(+r, g());
}