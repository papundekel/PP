#pragma once
#include "type_t.hpp"
#include "value_t.hpp"
#include "tuple_recursive.hpp"
#include "tuple_head_no_get.hpp"

namespace PP
{
	template <typename...>
	struct type_tuple {};
	template <typename Head, typename... Rest>
	struct type_tuple<Head, Rest...>
	{
		constexpr auto head() const noexcept
		{
			return type_v<Head>;
		}
		constexpr auto head_element() const noexcept
		{
			return type_v<type_t<Head>>;
		}
		constexpr auto pred() const noexcept
		{
			return type_tuple<Rest...>{};
		}
		constexpr auto operator[](value_wrap auto i) const noexcept
		{
			return tuple_recursive(tuple_head_no_get, i, *this);
		}
	};
	template <typename... T>
	constexpr inline type_tuple<T...> type_tuple_v = {};

	template <typename... T>
	constexpr auto tuple_count_implementation(type_tuple<T...> t) noexcept
	{
		return value_v<sizeof...(T)>;
	};
}
