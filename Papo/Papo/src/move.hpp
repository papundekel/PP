#pragma once
#include "range.hpp"
#include "move_assignable.hpp"

template <range_t Src, range_t Dest>
requires move_assignable_to<typename Src::base_t, typename Dest::base_t> && (Src::finite || Dest::finite)
auto move(Src src, Dest dest)
{
	for (; src.begin != src.end && dest.begin != dest.end; ++dest.begin, ++src.begin)
		*dest.begin = move(*src.begin);
	return dest.begin;
}