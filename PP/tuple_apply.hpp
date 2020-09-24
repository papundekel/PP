#pragma once
#include <utility>
#include "tuple_size.hpp"
#include "tuple_like.hpp"
#include "tuple_get.hpp"

namespace PP
{
	constexpr inline auto tuple_apply =
		[]<typename F, tuple_like Tuple>(F&& f, Tuple&& tuple) -> decltype(auto)
		{
			return
				[&f, &tuple]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto)
				{
					return std::forward<F>(f)(tuple_get<I>(std::forward<Tuple>(tuple))...);
				}(std::make_index_sequence<tuple_size_v<Tuple>>{});
		};
}
