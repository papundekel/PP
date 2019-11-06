#pragma once
#include "range.hpp"
#include "construct.hpp"
#include "move.hpp"

template <typename Src, typename Dest>
auto u_move(Src src, Dest dest)
{
	for (; src; ++dest, ++src)
		construct(+dest, move(*src));
	return dest;
}