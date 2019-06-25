#pragma once
#include "range.hpp"
#include "construct.hpp"

template <range_t Src, range_t Dest>
auto u_copy(Src src, Dest dest)
{
	for (; src && dest; ++dest, ++src)
		construct(dest.begin, *src);
	return dest.begin;
}