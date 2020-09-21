#pragma once
#include <tuple>
#include "functional/apply_partially.hpp"

namespace PP
{
	template <typename Head>
	constexpr auto tuple_prepend(Head&& head)
	{
		return apply_partially(tuple_apply,
			[head = std::forward<Head>(head)]<typename... T>(T&&... elements)
			{
				return std::tuple<std::decay_t<Head>, T&&...>(head, std::forward<T>(elements)...);
			});
	}
	template <typename Head, typename Tuple>
	constexpr auto tuple_prepend_no_copy(Head&& head, Tuple&& tuple)
	{
		return std::apply(
			[&head]<typename... T>(T&&... elements)
			{
				return std::forward_as_tuple(std::forward<Head>(head), std::forward<T>(elements)...);
			}, std::forward<Tuple>(tuple));
	}
}
