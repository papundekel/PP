#pragma once
#include "apply_partially_first.hpp"
#include "constant.hpp"
#include "construct_pack.hpp"
#include "empty_tuple.hpp"
#include "tuple_fold.hpp"
#include "tuple_make.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_concat, concepts::tuple auto&& l, concepts::tuple auto&& r)
	{
		auto t = tuple_forward(PP_F(r));
		return tuple_foldr(tuple_prepend,
		                   constant(forward_wrap(move(t))),
		                   PP_F(l));
	});

	PP_FUNCTOR(tuple_concats, concepts::tuple auto&& tuples)
	{
		// tuple_make is a dirty fix, it shouldn't be there
		return tuple_foldl(tuple_concat, constant(empty_tuple{}), PP_F(tuples));
	});

	constexpr inline auto tuple_concats_pack = tuple_concats | forward_as_tuple;
}
