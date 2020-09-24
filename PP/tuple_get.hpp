#pragma once
#include <cstddef>
#include "tuple_like.hpp"
#include "value_t.hpp"

namespace PP
{
	template <std::size_t I>
	constexpr inline auto tuple_get = []<tuple_like Tuple>(Tuple&& tuple) -> decltype(auto) { return get(value_t<I>{}, std::forward<Tuple>(tuple)); };
}
