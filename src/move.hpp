#pragma once
#include "move_.hpp"
#include "range.hpp"
#include "assignable.hpp"

template <typename Src, typename Dest>
requires range_type<Src>::v && range_type<Dest>::v && assignable<range_base<Src>&&, range_base<Dest>>::v && (Src::finite || Dest::finite)
auto move(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = move(*src);
	return dest;
}