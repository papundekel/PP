#pragma once
#include "tuple_forward_array.hpp"
#include "tuple_make_array.hpp"
#include "tuple_map.hpp"
#include "tuple_to_array.hpp"

namespace PP
{
	constexpr inline auto tuple_map_make_array = tuple_make_array | tuple_map;
	constexpr inline auto tuple_map_forward_array =
		tuple_forward_array | tuple_map;
	PP_FUNCTOR(tuple_map_to_array,
			   concepts::type auto	  t,
			   auto&&				  map,
			   concepts::tuple auto&& tuple)
	{
		return tuple_to_array(t, tuple_map(PP_FORWARD(map), PP_FORWARD(tuple)));
	});

	constexpr auto operator<(concepts::functor auto&& f,
							 concepts::tuple auto&&	  tuple)
	{
		return tuple_map_make_array(unwrap_functor(PP_FORWARD(f)),
									PP_FORWARD(tuple));
	}
	constexpr auto operator<<(concepts::functor auto&& f,
							  concepts::tuple auto&&   tuple) noexcept
	{
		return tuple_map_forward_array(unwrap_functor(PP_FORWARD(f)),
									   PP_FORWARD(tuple));
	}
}
