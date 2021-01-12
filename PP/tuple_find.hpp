#pragma once
#include "tuple_split.hpp"

namespace PP
{
	namespace detail
	{
		struct tuple_find_index_helper
		{
			constexpr std::size_t operator()(auto&& predicate, tuple_like auto&& tuple) const
			{
				auto split = tuple_split(PP_FORWARD(tuple));
				if constexpr (tuple_like<decltype(split)>)
				{
					if (PP_FORWARD(predicate)(tuple_get<0>(split)))
						return 0;
					else
						return 1 + (*this)(PP_FORWARD(predicate), tuple_get<1>(split));
				}
				else
					return 0;
			}
		};
	}

	constexpr inline auto tuple_find_index = detail::tuple_find_index_helper{};
}
