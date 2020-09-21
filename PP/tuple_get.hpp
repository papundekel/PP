#pragma once
#include "tuple_like.hpp"

namespace PP
{
	template <std::size_t I>
	constexpr inline auto tuple_get = []<tuple_like Tuple>(Tuple&& tuple) -> decltype(auto)
	{
		return std::get<I>(std::forward<Tuple>(tuple));
	};
}
