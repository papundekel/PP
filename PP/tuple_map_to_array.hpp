#pragma once
#include "functional/map_arguments.hpp"
#include "reference_wrapper.hpp"
#include "same.hpp"
#include "tuple_like.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	struct tuple_map_homo_deduce_return_type {};

	PP_FUNCTOR(tuple_map_to_array, auto&& map, tuple_like auto&& t, auto type = type_v<tuple_map_homo_deduce_return_type>)
	{
		return tuple_apply(
			[&map, t](auto&&... elements)
			{
				constexpr auto T = PP_COPY_TYPE(type);

				if constexpr (T == type_v<tuple_map_homo_deduce_return_type>)
				{
					constexpr auto one_type = same_types(PP_DECLTYPE(PP_FORWARD(map)(PP_FORWARD(elements)))...);

					if constexpr (is_reference(one_type))
						return std::array<reference_wrapper<!PP_GET_TYPE(one_type)>, sizeof...(elements)>{ PP_FORWARD(map)(PP_FORWARD(elements))... };
					else
						return std::array{ PP_FORWARD(map)(PP_FORWARD(elements))... };
				}
				else
				{
					if constexpr (is_reference(T))
						return std::array<reference_wrapper<PP_GET_TYPE(T)>, sizeof...(elements)>{ PP_FORWARD(map)(PP_FORWARD(elements))... };
					else
						return std::array<PP_GET_TYPE(T), sizeof...(elements)>{ PP_FORWARD(map)(PP_FORWARD(elements))... };
				}

			}, PP_FORWARD(t));
	}};
}
