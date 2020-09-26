#pragma once
#include <tuple>
#include <type_traits>
#include <array>
#include "reference_wrapper.hpp"
#include "tuple_like.hpp"

namespace PP
{
	struct tuple_map_homo_deduce_return_type {};

	constexpr inline auto tuple_map_to_array =
		[]<typename Map, tuple_like Tuple, typename Type = tuple_map_homo_deduce_return_type>
		(Map&& map, Tuple&& tuple, Type = {})
		{
			return std::apply(
				[&map]<typename... T>(T&&... elements)
				{
					if constexpr (std::is_same_v<Type, tuple_map_homo_deduce_return_type>)
						return std::array{ std::forward<Map>(map)(std::forward<T>(elements))... };
					else
					{
						using U = PP::get_type<Type>;
						if constexpr (std::is_reference_v<U>)
							return std::array<reference_wrapper<U>, sizeof...(T)>{ std::forward<Map>(map)(std::forward<T>(elements))... };
						else
							return std::array<U, sizeof...(T)>{ std::forward<Map>(map)(std::forward<T>(elements))... };
					}
				}, std::forward<Tuple>(tuple));
		};
}
