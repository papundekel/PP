#pragma once
#include "declval.hpp"
#include "functor.hpp"
#include "tuple.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto tuple_map_helper(auto&& map, auto&& element) noexcept
		{
			return [m = PP_FORWARD_WRAP(map),
					e = PP_FORWARD_WRAP(element)]() -> decltype(auto)
			{
				return m--(e--);
			};
		}
	}

	PP_FUNCTOR(tuple_map, auto&& map, concepts::tuple auto&& t)
	{
		return functor(
			[m = PP_FORWARD_WRAP(map)](auto&&... elements)
			{
				return tuple(
					in_place,
					detail::tuple_map_helper(m--, PP_FORWARD(elements))...);
			})[PP_FORWARD(t)];
	});

	constexpr auto operator+(concepts::functor auto&& f,
							 concepts::tuple auto&& tuple)
	{
		return tuple_map(unwrap_functor(PP_FORWARD(f)), PP_FORWARD(tuple));
	}
}
