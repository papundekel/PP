#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <range_t Src, range_t Dest>
requires assignable_to<base_type<Src>, base_type<Dest>> && (Src::finite || Dest::finite)
auto copy(Src src, Dest dest)
{
	for (; !src.empty() && !dest.empty(); ++dest, ++src)
		*dest.begin = *src.begin;
	return dest.begin;
}