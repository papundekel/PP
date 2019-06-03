#pragma once
#include "range.hpp"
#include "construct.hpp"

template <range_t Src, range_t Dest>
auto u_copy(Src src, Dest dest)
{
	for (; src.begin != src.end && dest.begin != src.end; ++dest.begin, ++src.begin)
		construct(dest.begin, *src.begin);
	return dest.begin;
}