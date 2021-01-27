#pragma once
#include "tuple_fold.hpp"
#include "tuple_split.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_fold1, concepts::value auto left, auto&& f, concepts::tuple auto&& tuple)
	{
		auto [head, tail] = tuple_split(PP_FORWARD(tuple));
		return tuple_fold(left, PP_FORWARD(f), PP_FORWARD(head), PP_FORWARD(tail));
	}};

	constexpr inline auto tuple_foldl1 = tuple_fold1 * value_true;
	constexpr inline auto tuple_foldr1 = tuple_fold1 * value_false;
}
