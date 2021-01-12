#pragma once
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	template <typename... Types>
	struct type_tuple {};
	template <typename T, typename... Types>
	struct type_tuple<T, Types...>
	{
		template <auto I>
		constexpr auto operator[](value_t<I>) const noexcept
		{
			if constexpr (I == 0)
				return type_v<T>;
			else
				return type_tuple<Types...>{}[value_v<I - 1>];
		};
	};
	template <typename... Types>
	constexpr inline type_tuple<Types...> type_tuple_v = {};

	template <typename... Types>
	constexpr auto get(auto i, type_tuple<Types...> t) noexcept
	{
		return t[i];
	};
	template <typename... Types>
	constexpr auto size_implementation(type_t<type_tuple<Types...>>) noexcept
	{
		return sizeof...(Types);
	};
}
