#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <range_c Src, range_c Dest>
requires assignable_to_c<range_base<Src>, range_base<Dest>> && (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = *src;
	return dest;
}