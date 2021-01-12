#pragma once
#include "../integer_sequence.hpp"
#include "../forward.hpp"
#include "../functional/functor.hpp"
#include "../tuple.hpp"
#include "constant.hpp"
#include "id.hpp"

namespace PP
{
	namespace detail
	{
		constexpr decltype(auto) map_arguments_element_helper(auto maps, auto i, auto maps_size)
		{
			if constexpr (i < maps_size)
				return get(i, maps);
			else
				return id_weak;
		}
		template <std::size_t... I>
		constexpr decltype(auto) map_arguments_helper(auto& f, auto maps, auto maps_size, std::index_sequence<I...>, auto&&... args)
		{
			return f(map_arguments_element_helper(maps, PP::value_v<I>, maps_size)(PP_FORWARD(args))...);
		}
	}

	PP_FUNCTOR(map_arguments, auto&& f, auto&&... maps)
	{
		return functor{
			[f = PP_FORWARD(f), ...maps = PP_FORWARD(maps)](auto&&... args) -> decltype(auto)
			{
				return detail::map_arguments_helper
					( f
					, std::forward_as_tuple(maps...)
					, PP::value_v<sizeof...(maps)>
					, std::make_index_sequence<sizeof...(args)>{}
					, PP_FORWARD(args)...);
			}};
	}};
}
