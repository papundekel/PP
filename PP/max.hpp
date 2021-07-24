#pragma once
#include "functor.hpp"
#include "view.hpp"

namespace PP
{
PP_FUNCTOR(max, auto&& comparer, concepts::view auto&& v)
{
	auto [begin, end] = view::begin_end(PP_F(v));

	if (begin == end)
		return end;

	auto max_i = begin;

	++begin;

	for (; begin != end; ++begin)
	{
		if (PP_F(comparer)(*max_i, *begin))
			max_i = begin;
	}

	return max_i;
});
}
