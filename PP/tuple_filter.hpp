#pragma once
#include "empty_tuple.hpp"
#include "get_value.hpp"
#include "tuple_fold.hpp"
#include "tuple_make.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_filter, concepts::value auto predicate, concepts::tuple auto&& t)
	{
		return tuple_foldr([]
			(concepts::value auto element, concepts::tuple auto tail)
			{
				if constexpr (PP_GET_VALUE(predicate)(PP_GET_VALUE(element)))
					return !tuple_prepend(element, tail);
				else
					return tail;
			},
			empty_tuple{}, PP_FORWARD(t));
	}};
}
