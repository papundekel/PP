#pragma once
#include "tuple_apply.hpp"
#include "tuple_like.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_all, auto&& predicate, concepts::tuple auto&& t)
	{
		return tuple_apply(
			[&predicate](auto&&... elements) -> decltype(auto)
			{
				return (PP_FORWARD(predicate)(PP_FORWARD(elements)) && ...);
			}, PP_FORWARD(t));
	}};
}
