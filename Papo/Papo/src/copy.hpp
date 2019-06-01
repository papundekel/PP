#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <range_t Dest, range_t Src>
requires assignable_to<typename Src::base_t, typename Dest::base_t> && (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; src.begin != src.end && dest.begin != dest.end; ++dest.begin, ++src.begin)
		*dest.begin = *src.begin;
	return dest.begin;
}