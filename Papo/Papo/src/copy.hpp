#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <range_t Src, range_t Dest>
requires assignable_to<range_base<Src>, range_base<Dest>> && (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = *src;
	return dest.begin;
}