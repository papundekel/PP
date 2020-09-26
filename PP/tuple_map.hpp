#pragma once
#include <tuple>
#include "tuple_apply.hpp"
#include <type_traits>

namespace PP
{
	template <bool copy = true>
	constexpr inline auto tuple_map =
		[](auto map)
		{
			return tuple_apply<>(
				[map = std::move(map)]<typename... T>(T&&... t)
				{
					return std::tuple<decltype(map(std::forward<T>(t)))...>(map(std::forward<T>(t))...);
				});
		};
	template <>
	constexpr inline auto tuple_map =
		[](auto& map)
		{
			return tuple_apply<>(
				[&map]<typename... T>(T&&... t)
				{
					return std::make_tuple(map(std::forward<T>(t))...);
				});
		};
}
