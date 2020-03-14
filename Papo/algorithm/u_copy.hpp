#pragma once
#include "range.hpp"
#include "construct.hpp"

template <typename Src, typename Dest>
requires range_type(type<Src>{}) && range_type(type<Dest>{})
auto u_copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		construct(+dest, *src);
	return dest;
}