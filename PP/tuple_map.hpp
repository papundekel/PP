#pragma once
#include "declval.hpp"
#include "functional/functor.hpp"
#include "tuple.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_map, auto&& map, concepts::tuple auto&& t)
	{
		return functor(
			[&map](auto&&... elements)
			{
				return tuple<decltype(declval(PP_DECLTYPE(unwrap_functor(
					PP_FORWARD(map))))(declval(PP_DECLTYPE(elements))))...>(
					placeholder,
					unwrap_functor(PP_FORWARD(map))(PP_FORWARD(elements))...);
			})[PP_FORWARD(t)];
	});

	constexpr auto operator+(concepts::functor auto&& f,
							 concepts::tuple auto&&	  tuple)
	{
		return tuple_map(unwrap_functor(PP_FORWARD(f)), PP_FORWARD(tuple));
	}
}
