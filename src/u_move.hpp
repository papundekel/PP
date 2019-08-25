#pragma once
#include "range.hpp"
#include "construct.hpp"
#include "move.hpp"

template <typename it1, typename it1_end, typename it2, typename it2_end>
it2 u_move(range<it1, it1_end> src, range<it2, it2_end> dest)
{
	for (; src.begin != src.end; ++dest.begin, ++src.begin)
		construct(dest.begin, move(*src.begin));
	return dest.begin;
}