#pragma once
#include "iterator.hpp"
#include "construct.hpp"
#include "move.hpp"

template <iterator it1, iterator it2>
auto u_move_backward_n(size_t count, it1 srcEnd, it2 destEnd)
{
	for (size_t i = 0; i != count; ++i)
		construct(--destEnd, move(*(--srcEnd)));
	return destEnd;
}