#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "construct.hpp"
#include "move.hpp"

template <typename it1, typename it2>
enable_if<is_iterator<it1> && is_iterator<it2>,
it2> u_move_backward_n(size_t count, it1 srcEnd, it2 destEnd)
{
	for (size_t i = 0; i != count; ++i)
		construct(--destEnd, move(*(--srcEnd)));
	return destEnd;
}