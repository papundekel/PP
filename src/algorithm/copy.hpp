#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename Src, typename Dest>
requires range_type<Src> &&
		 range_type<Dest> &&
		 assignable<range_base<Src>, range_base<Dest>> &&
		 (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = *src;
	return dest;
}