#pragma once
#include "tuple_like.hpp"

namespace PP
{
	namespace detail
	{
		template <std::size_t... I>
		constexpr bool tuple_equal_helper(const auto& a, const auto& b, std::index_sequence<I...>)
		{
			return ((std::get<I>(a) == std::get<I>(b)) && ...);
		}
	}

	template <PP::tuple_like A, PP::tuple_like B>
	constexpr auto operator==(const A& a, const B& b)
	{
		return std::tuple_size_v<A> == std::tuple_size_v<B> && detail::tuple_equal_helper(a, b, std::make_index_sequence<std::tuple_size_v<A>>{});
	}
}
