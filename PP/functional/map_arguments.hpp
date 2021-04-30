#pragma once
#include "../functional/functor.hpp"
#include "../tuple.hpp"
#include "../tuple_count.hpp"
#include "../tuple_get.hpp"
#include "../utility/forward.hpp"
#include "../utility/move.hpp"
#include "../value_sequence.hpp"
#include "id.hpp"

namespace PP
{
	namespace detail
	{
		constexpr decltype(auto) map_arguments_element_helper(
			auto				 maps,
			concepts::value auto i)
		{
			if constexpr (i < tuple_type_count(PP_DECLTYPE(maps)))
				return tuple_get(i, move(maps));
			else
				return id_forward;
		}
		template <auto... I>
		constexpr decltype(auto) map_arguments_helper(auto& f,
													  auto	maps,
													  value_sequence<I...>,
													  auto&&... args)
		{
			return f(map_arguments_element_helper(maps, value<I>)(
				PP_FORWARD(args))...);
		}
	}

	PP_FUNCTOR(map_arguments, auto&& f, auto&&... maps)
	{
		return functor(
			[f = unwrap_functor(PP_FORWARD(f)),
			 ... maps = unwrap_functor(PP_FORWARD(maps))](
				auto&&... args) -> decltype(auto)
			{
				return detail::map_arguments_helper(
					f,
					forward_as_tuple(maps...),
					make_value_sequence(value<sizeof...(args)>),
					PP_FORWARD(args)...);
			});
	});
}
