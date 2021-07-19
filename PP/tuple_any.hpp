#pragma once
#include "tuple_apply.hpp"
#include "tuple_concept.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_any, auto&& predicate, concepts::tuple auto&& t)
		-> decltype(auto)
	{
		return functor(
			[&predicate](auto&&... elements) -> decltype(auto)
			{
				return (unwrap_functor(PP_F(predicate))(PP_F(elements)) || ...);
			})[PP_F(t)];
	});

	constexpr decltype(auto) operator||(concepts::functor auto&& f,
	                                    concepts::tuple auto&& tuple)
	{
		return tuple_any(unwrap_functor(PP_F(f)), PP_F(tuple));
	}
}
