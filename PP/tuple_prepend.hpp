#pragma once
#include <tuple>
#include "tuple_apply.hpp"

namespace PP
{
	template <bool copy = true>
	constexpr inline auto tuple_prepend = [](auto head)
	{
		return tuple_apply<>(
			[h = std::move(head)]<typename... T>(T&&... elements)
			{
				return std::tuple<decltype(head), T&&...>(h, std::forward<T>(elements)...);
			});
	};
	template <>
	constexpr inline auto tuple_prepend<false> = [](auto& head)
	{
		return tuple_apply<>(
			[&head]<typename... T>(T&&... elements)
			{
				return std::tuple<std::remove_cv_t<decltype(head)>, T&&...>(head, std::forward<T>(elements)...);
			});
	};
}
