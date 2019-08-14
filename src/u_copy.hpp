#pragma once
#include "range.hpp"
#include "construct.hpp"

template <typename Src, typename Dest>
requires range_type<Src>::v && range_type<Dest>::v
auto u_copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		construct(dest.begin, *src);
	return dest.begin;
}