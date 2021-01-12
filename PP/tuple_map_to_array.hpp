#pragma once
#include <tuple>
#include <type_traits>
#include <array>
#include "reference_wrapper.hpp"
#include "functional/map_arguments.hpp"
#include "tuple_like.hpp"
#include "tuple_apply.hpp"
#include "same.hpp"

namespace PP
{
	struct tuple_map_homo_deduce_return_type {};

	constexpr inline auto tuple_map_to_array =
		[]<typename Type = tuple_map_homo_deduce_return_type>
		(auto&& map, tuple_like auto&& tuple, Type = {})
		{
			return tuple_apply(
				[&map](auto&&... elements)
				{
					if constexpr (std::is_same_v<Type, tuple_map_homo_deduce_return_type>)
					{
						constexpr auto one_type = same_types(PP::type_v<decltype(std::forward<decltype(map)>(map)(std::forward<decltype(elements)>(elements)))>...);

						if constexpr (PP::map_v(PP::template_v<std::is_lvalue_reference>, one_type))
							return std::array<reference_wrapper<PP::get_type<decltype(one_type)>>, sizeof...(elements)>{ std::forward<decltype(map)>(map)(std::forward<decltype(elements)>(elements))... };
						else
							return std::array{ std::forward<decltype(map)>(map)(std::forward<decltype(elements)>(elements))... };
					}
					else
					{
						using U = PP::get_type<Type>;
						if constexpr (std::is_reference_v<U>)
							return std::array<reference_wrapper<U>, sizeof...(elements)>{ std::forward<decltype(map)>(map)(std::forward<decltype(elements)>(elements))... };
						else
							return std::array<U, sizeof...(elements)>{ std::forward<decltype(map)>(map)(std::forward<decltype(elements)>(elements))... };
					}
					
				}, std::forward<decltype(tuple)>(tuple));
		};
}
