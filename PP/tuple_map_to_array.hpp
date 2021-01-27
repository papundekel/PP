#pragma once
#include "tuple_map.hpp"
#include "tuple_to_array.hpp"

namespace PP
{
	constexpr inline auto tuple_map_make_array = tuple_make_array * type_void | tuple_map;
	constexpr inline auto tuple_map_forward_array = tuple_forward_array * type_void | tuple_map;

	constexpr auto operator<(concepts::functor auto&& f, concepts::tuple auto&& tuple)
	{
		return tuple_map_make_array(PP_FORWARD(f).f, PP_FORWARD(tuple));
	}
	constexpr auto operator<<(concepts::functor auto&& f, concepts::tuple auto&& tuple) noexcept
	{
		return tuple_map_forward_array(PP_FORWARD(f).f, PP_FORWARD(tuple));
	}
}
