#pragma once
#include "range.hpp"
#include "move.hpp"
template <typename Src, typename Dest>
auto move_backward(Src src, Dest dest)
{
	while (src)
		*(--dest.end) = move(*(--src.end));
	return dest.end;
}