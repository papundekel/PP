#pragma once
#include "tuple_apply.hpp"
#include "tuple_like.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_all, auto&& predicate, concepts::tuple auto&& t) -> decltype(auto)
	{
		return tuple_apply(
			[&predicate](auto&&... elements) -> decltype(auto)
			{
				return (PP_FORWARD(predicate)(PP_FORWARD(elements)) && ...);
			}, PP_FORWARD(t));
	}};

	constexpr decltype(auto) operator&&(concepts::functor auto&& f, concepts::tuple auto&& tuple)
	{
		return tuple_all(PP_FORWARD(f).f, PP_FORWARD(tuple));
	}
}
