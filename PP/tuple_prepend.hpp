#pragma once
#include <tuple>
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	template <bool copy = true>
	constexpr inline auto tuple_prepend = [](auto head)
	{
		return apply_partially<false>(tuple_apply,
			[head = std::move(head)]<typename... T>(T&&... elements)
			{
				return std::tuple<decltype(head), T&&...>(head, std::forward<T>(elements)...);
			});
	};
	template <>
	constexpr inline auto tuple_prepend<false> = [](auto& head)
	{
		return apply_partially<false>(tuple_apply,
			[&head]<typename... T>(T&&... elements)
			{
				return std::tuple<decltype(head), T&&...>(head, std::forward<T>(elements)...);
			});
	};
}
