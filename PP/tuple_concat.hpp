#pragma once
#include "tuple_fold.hpp"
#include "tuple_make.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_concat, concepts::tuple auto&& l, concepts::tuple auto&& r)
	{
		return tuple_foldr(tuple_prepend,
						   tuple_forward(PP_FORWARD(r)),
						   PP_FORWARD(l));
	});

	PP_FUNCTOR(tuple_concats, concepts::tuple auto&& tuples)
	{
		return tuple_foldl(tuple_make | tuple_concat,
						   empty_tuple{},
						   PP_FORWARD(tuples));
	});

	constexpr inline auto tuple_concats_pack = tuple_concats | forward_as_tuple;
}
