#pragma once
#include "range.hpp"
#include "move_assignable.hpp"

template <range_t Src, range_t Dest>
requires move_assignable_to<range_base<Src>, range_base<Dest>> && (Src::finite || Dest::finite)
auto move(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = move(*src);
	return dest.begin;
}