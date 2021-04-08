#pragma once
#include "tuple_fold.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_concat, concepts::tuple auto&& l, concepts::tuple auto&& r)
	{
		return tuple_foldr(tuple_prepend, PP_FORWARD(r), PP_FORWARD(l));
	});

	PP_FUNCTOR(tuple_concats, concepts::tuple auto&& l)
	{
		return tuple_foldl(tuple_concat, empty_tuple{}, PP_FORWARD(l));
	});
}
