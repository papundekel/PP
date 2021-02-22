#pragma once
#include "empty_tuple.hpp"
#include "forward_wrap.hpp"
#include "get_value.hpp"
#include "tuple_fold.hpp"
#include "tuple_make.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_filter, auto&& predicate, concepts::tuple auto&& t)
	{
		return tuple_foldr([predicate_wrap = PP_FORWARD_WRAP(predicate)]
			(auto&& element, concepts::tuple auto tail)
			{
				if constexpr (PP_GET_VALUE(predicate_wrap.unwrap()(PP_FORWARD(element))))
					return !tuple_prepend(PP_FORWARD(element), move(tail));
				else
					return tail;
			},
			empty_tuple{}, PP_FORWARD(t));
	});
}
