#pragma once
#include "range.hpp"
#include "callable.hpp"
#include "move_assignable.hpp"
template <range_t R, callable G>
requires move_assignable_to<return_t<G>, base_type<R>>
void generate(R r, G g)
{
	for (; r.begin != r.end; ++r.begin)
		*r.begin = g();
}