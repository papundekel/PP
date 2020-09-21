#pragma once
#include <tuple>

namespace PP
{
	template <typename Map, typename Tuple>
	constexpr auto tuple_map(Map&& map, Tuple&& tuple)
	{
		return std::apply(
			[&map]<typename... T>(T&&... t)
			{
				return std::make_tuple(std::forward<Map>(map)(std::forward<T>(t))...);
			}, std::forward<Tuple>(tuple));
	}
}
