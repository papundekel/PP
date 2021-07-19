#pragma once
#include "construct_pack.hpp"
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "operators.hpp"
#include "tuple_forward_array.hpp"
#include "tuple_make_array.hpp"
#include "tuple_map.hpp"
#include "tuple_to_array.hpp"
#include "wrap.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_map_to_array,
	           concepts::type auto t,
	           auto&& map,
	           concepts::tuple auto&& tuple)
	{
		return (array_constructor_typed * value_true *
		        t)[/*PP::functor(
		               [m = forward_wrap(unwrap_functor(PP_F(map)))](
		                   auto&& ee)
		               {
		                   return m * PP_FORWARD_WRAP(ee);
		               })*/
		           (apply_partially_first * PP_FORWARD_WRAP(map) |
		            PP::functor(
						[](auto&& x)
						{
							return forward_wrap(PP_F(x));
						})) +
		           PP_F(tuple)];
	});

	namespace detail
	{
		constexpr auto tuple_map_array_type(auto&& map, auto&& tuple)
		{
			if constexpr (requires
			              {
							  PP_F(tuple)[value_0];
						  })
				return PP_DECLTYPE(PP_F(map)(PP_F(tuple)[value_0]));
			else
				return type_char;
		}
	}

	PP_FUNCTOR(tuple_map_make_array, auto&& map, concepts::tuple auto&& tuple)
	{
		return tuple_map_to_array(
			~detail::tuple_map_array_type(PP_F(map), PP_F(tuple)),
			PP_F(map),
			PP_F(tuple));
	});

	PP_FUNCTOR(tuple_map_forward_array,
	           auto&& map,
	           concepts::tuple auto&& tuple)
	{
		return tuple_map_to_array(
			detail::tuple_map_array_type(PP_F(map), PP_F(tuple)),
			PP_F(map),
			PP_F(tuple));
	});

	constexpr auto operator<(concepts::wrap auto&& f,
	                         concepts::tuple auto&& tuple)
	{
		return tuple_map_make_array(unwrap(PP_F(f)), PP_F(tuple));
	}
	constexpr auto operator<<(concepts::wrap auto&& f,
	                          concepts::tuple auto&& tuple) noexcept
	{
		return tuple_map_forward_array(unwrap(PP_F(f)), PP_F(tuple));
	}
}
