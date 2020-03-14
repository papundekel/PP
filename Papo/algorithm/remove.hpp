#pragma once
#include "enable_if.hpp"
#include "range.hpp"
#include "callable.hpp"
#include "move.hpp"
#include "find.hpp"
#include "next.hpp"

template <Range R, callable_r<bool, range_base<R>> F>
auto remove(R r, F f)
{
	auto i = find(r, f);
	if (i != r.end)
		for (r.begin = next(i); r.begin != r.end; ++r.begin)
			if (!f(*r.begin))
			{
				*i = move(*r.begin);
				++i;
			}
	return i;
}