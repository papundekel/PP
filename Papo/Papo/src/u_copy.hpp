#pragma once
#include "range.hpp"
#include "construct.hpp"

template <range_t Src, range_t Dest>
auto u_copy(Src src, Dest dest)
{
	for (; !src.empty() && !dest.empty(); ++dest, ++src)
		construct(dest.begin, *src.begin);
	return dest.begin;
}