#pragma once
#include <utility>
#include "tuple_size.hpp"
#include "tuple_like.hpp"
#include "tuple_get.hpp"

namespace PP
{
	constexpr inline auto tuple_apply =
		[](auto&& f, tuple_like auto&& tuple) constexpr -> decltype(auto)
		{
			return
				[&f, &tuple]<std::size_t... I>(std::index_sequence<I...>) constexpr -> decltype(auto)
				{
					return std::forward<decltype(f)>(f)(tuple_get<I>(std::forward<decltype(tuple)>(tuple))...);
				}(std::make_index_sequence<tuple_size_v<decltype(tuple)>>{});
		};
}
