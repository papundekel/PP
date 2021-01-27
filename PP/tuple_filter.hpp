#pragma once
#include "empty_tuple.hpp"
#include "tuple_fold.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_filter, concepts::value auto predicate, concepts::tuple auto&& t)
	{
		return tuple_foldr([]
			(auto&& element, auto&& tail)
			{
				if constexpr (PP_COPY_VALUE(predicate)(PP_FORWARD(element)))
					return tuple_prepend(PP_FORWARD(element), PP_FORWARD(tail));
				else
					return PP_FORWARD(tail);
			},
			empty_tuple{}, PP_FORWARD(t));
	}};
}
