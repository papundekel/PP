#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "construct.hpp"
#include "move.hpp"

template <typename it1, typename it2>
enable_if<is_iterator<it1> && is_iterator<it2>,
it2> u_move_n(it1 srcBegin, size_t count, it2 destBegin)
{
	for (size_t i = 0; i != count; ++i, ++destBegin, ++srcBegin)
		construct(destBegin, move(*srcBegin));
	return destBegin;
}