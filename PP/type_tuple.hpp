#pragma once
#include <tuple>
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	template <typename... Types>
	struct type_tuple {};

	template <typename... Types>
	constexpr inline type_tuple<Types...> type_tuple_v = {};

	template <std::size_t I, typename... Types>
	constexpr auto& get(value_t<I>, type_tuple<Types...>) noexcept
	{
		return type_v<std::tuple_element_t<I, std::tuple<Types...>>>;
	};
}

namespace std
{
	template <typename... Types>
	struct tuple_size<PP::type_tuple<Types...>> : public tuple_size<std::tuple<Types...>> {};

	template <std::size_t I, typename... Types>
	struct tuple_element<I, PP::type_tuple<Types...>> : public tuple_element<I, std::tuple<PP::type_t<Types>...>> {};
}
