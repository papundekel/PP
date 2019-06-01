#pragma once
#include "enable_if.hpp"
#include "range.hpp"
#include "is_callable.hpp"
#include "base_type.hpp"
#include "move.hpp"
#include "find_if.hpp"
#include "next.hpp"

template <typename it, typename it_end, typename F>
it remove_if(range<it, it_end> r, F f)
{
	static_assert(is_callable<bool, F, base_type<it>>);

	auto i = find_if(r, f);
	if (i != r.end)
		for (r.begin = next(i); r.begin != r.end; ++r.begin)
			if (!f(*r.begin))
			{
				*i = move(*r.begin);
				++i;
			}
	return i;
}