#pragma once
#include "../forward.hpp"
#include "../functional/functor.hpp"
#include "../std_integer_sequence.hpp"
#include "../tuple.hpp"
#include "../tuple_size.hpp"
#include "../tuple_like.hpp"
#include "id.hpp"
#include "constant.hpp"

namespace PP
{
	namespace detail
	{
		constexpr decltype(auto) map_arguments_element_helper(tuple_like auto maps, value_wrap auto i)
		{
			constexpr auto maps_size = tuple_type_size(PP_DECLTYPE(maps));

			if constexpr (i < maps_size)
				return get(i, maps);
			else
				return id_weak;
		}
		template <std::size_t... I>
		constexpr decltype(auto) map_arguments_helper(auto& f, tuple_like auto maps, std::index_sequence<I...>, auto&&... args)
		{
			return f(map_arguments_element_helper(maps, value_v<I>)(PP_FORWARD(args))...);
		}
	}

	PP_FUNCTOR(map_arguments, auto&& f, auto&&... maps)
	{
		return functor{
			[f = PP_FORWARD(f), ...maps = PP_FORWARD(maps)](auto&&... args) -> decltype(auto)
			{
				return detail::map_arguments_helper
					( f
					, forward_as_tuple(maps...)
					, std::make_index_sequence<sizeof...(args)>{}
					, PP_FORWARD(args)...);
			}};
	}};
}
