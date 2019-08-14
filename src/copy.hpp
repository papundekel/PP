#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename Src, typename Dest>
requires range_type<Src>::v && range_type<Dest>::v && assignable_to<range_base<Src>, range_base<Dest>>::v && (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = *src;
	return dest;
}