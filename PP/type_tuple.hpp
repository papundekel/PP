#pragma once
#include <tuple>
#include "type_t.hpp"

namespace PP
{
	template <typename... Types>
	struct type_tuple {};

	template <typename... Types>
	constexpr inline type_tuple<Types...> type_tuple_v = {};
}

namespace std
{
	template <std::size_t I, typename... Types>
	constexpr auto get(PP::type_tuple<Types...>) noexcept
	{
		return PP::type_v<std::tuple_element_t<I, std::tuple<Types...>>>;
	}
}
