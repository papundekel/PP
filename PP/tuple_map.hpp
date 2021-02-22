#pragma once
#include "tuple.hpp"
#include "declval.hpp"
#include "functional/functor.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_map, auto&& map, concepts::tuple auto&& t)
	{
		return functor([&map]
			(auto&&... elements)
			{
				return tuple<decltype(declval(PP_DECLTYPE(map))(declval(PP_DECLTYPE(elements))))...>
					(placeholder, PP_FORWARD(map)(PP_FORWARD(elements))...);
			})[PP_FORWARD(t)];
	});

	constexpr auto operator+(concepts::functor auto&& f, concepts::tuple auto&& tuple)
	{
		return tuple_map(PP_FORWARD(f).f, PP_FORWARD(tuple));
	}
}
