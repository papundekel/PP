#pragma once
#include "move_.hpp"
#include "range.hpp"
#include "assignable.hpp"

template <typename Src, typename Dest>
requires range_type(type<Src>{}) &&
		 range_type(type<Dest>{}) &&
		 assignable(make_reference_rvalue(range_base(type<Src>{})), range_base(type<Dest>{})) &&
		 (Src::finite || Dest::finite)
auto move(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		*dest = move(*src);
	return dest;
}