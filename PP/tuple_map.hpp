#pragma once
#include <tuple>
#include "tuple_apply.hpp"

namespace PP
{
	template <bool copy = true>
	constexpr inline auto tuple_map =
		[](auto map)
		{
			return apply_partially<false>(tuple_apply,
				[map = std::move(map)]<typename... T>(T&&... t)
				{
					return std::forward_as_tuple(map(std::forward<T>(t))...);
				});
		};
	template <>
	constexpr inline auto tuple_map =
		[](auto& map)
		{
			return apply_partially<false>(tuple_apply,
				[&map ]<typename... T>(T&&... t)
				{
					return std::forward_as_tuple(map(std::forward<T>(t))...);
				});
		};
}
