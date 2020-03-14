#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "move_assignable.hpp"
template <Range R, callable G>
requires move_assignable<return_t<G>, range_base<R>>
void generate(R r, G g)
{
	for (; r.begin != r.end; ++r.begin)
		*r.begin = g();
}