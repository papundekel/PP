#pragma once
#include "tuple_foldr.hpp"

namespace PP
{
	struct tuple_find_fail {};

	namespace detail
	{
		struct tuple_find_index_helper
		{
			constexpr std::size_t operator()(auto&& predicate, tuple_like auto&& tuple) const
			{
				if constexpr (tuple_size(tuple_map_default<decltype(tuple)>(constant<>(std::tuple<>{}))) != 0)
				{
					auto [head, tail] = tuple_split(std::forward<decltype(tuple)>(tuple));

					if (std::forward<decltype(predicate)>(predicate)(head))
						return 0;
					else
						return 1 + (*this)(std::forward<decltype(predicate)>(predicate), tail);
				}
				else
					return 0;
			}
		};
	}

	constexpr inline auto tuple_find_index = detail::tuple_find_index_helper{};
}
