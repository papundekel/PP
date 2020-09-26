#pragma once
#include <utility>
#include "tuple_size.hpp"
#include "tuple_like.hpp"
#include "tuple_get.hpp"

namespace PP
{
	template <bool copy = true>
	constexpr inline auto tuple_apply =
		[](auto f)
		{
			return
				[g = std::move(f)]<tuple_like Tuple>(Tuple&& tuple) -> decltype(auto)
				{
					return
						[&g, &tuple]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto)
						{
							return g(tuple_get<I>(std::forward<Tuple>(tuple))...);
						}(std::make_index_sequence<tuple_size_v<Tuple>>{});
				};
		};
	template <>
	constexpr inline auto tuple_apply<false> =
		[](auto& f)
		{
			return
				[&f]<tuple_like Tuple>(Tuple&& tuple) -> decltype(auto)
				{
					return
						[&f, &tuple]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto)
						{
							return f(tuple_get<I>(std::forward<Tuple>(tuple))...);
						}(std::make_index_sequence<tuple_size_v<Tuple>>{});
				};
		};
}
