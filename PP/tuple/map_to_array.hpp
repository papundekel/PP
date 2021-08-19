#pragma once
#include "../construct_pack.hpp"
#include "../forward_wrap.hpp"
#include "../functor.hpp"
#include "../operators.hpp"
#include "../wrap.hpp"
#include "forward_array.hpp"
#include "make_array.hpp"
#include "map.hpp"
#include "to_array.hpp"

namespace PP::detail
{
constexpr auto tuple_map_array_type(auto&& map, auto&& tuple)
{
	if constexpr (requires
	              {
		              PP_F(tuple)[value_0];
	              })
		return PP_DT(PP_F(map)(PP_F(tuple)[value_0]));
	else
		return type_char;
}
}

namespace PP::tuple
{
PP_FUNCTOR(map_to_array,
           concepts::type auto&& t,
           auto&& map,
           concepts::tuple auto&& tuple)
{
	return (array::construct * t *
	        in_place)[(apply_partially_first * PP_FW(map) |
	                   PP::functor(
	                       [](auto&& x)
	                       {
		                       return forward_wrap(PP_F(x));
	                       })) +
	                  PP_F(tuple)];
});

PP_FUNCTOR(map_make_array, auto&& map, concepts::tuple auto&& tuple)
{
	return map_to_array(~detail::tuple_map_array_type(PP_F(map), PP_F(tuple)),
	                    PP_F(map),
	                    PP_F(tuple));
});

PP_FUNCTOR(map_forward_array, auto&& map, concepts::tuple auto&& tuple)
{
	return map_to_array(detail::tuple_map_array_type(PP_F(map), PP_F(tuple)),
	                    PP_F(map),
	                    PP_F(tuple));
});
}

constexpr auto operator<(PP::concepts::wrap auto&& f,
                         PP::concepts::tuple auto&& t)
{
	return PP::tuple::map_make_array(PP_UF(f), PP_F(t));
}

constexpr auto operator<<(PP::concepts::wrap auto&& f,
                          PP::concepts::tuple auto&& t) noexcept
{
	return PP::tuple::map_forward_array(PP_UF(f), PP_F(t));
}
