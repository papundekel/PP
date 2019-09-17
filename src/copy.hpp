#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename Src, typename Dest>
requires range_type(type<Src>{}) &&
		 range_type(type<Dest>{}) &&
		 assignable(range_base(type<Src>{}), range_base(type<Dest>{})) &&
		 (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = *src;
	return dest;
}