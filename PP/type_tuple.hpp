#pragma once
#include "type_t.hpp"
#include "get_value.hpp"

namespace PP
{
	template <typename...>
	struct type_tuple
	{
		static constexpr std::size_t type_tuple_size = 0;
	};
	template <typename T, typename... Types>
	struct type_tuple<T, Types...>
	{
		constexpr auto operator[](auto i) const noexcept
		{
			constexpr auto I = PP_COPY_VALUE(i);

			if constexpr (I == value_0)
				return type_v<T>;
			else
				return type_tuple<Types...>{}[I - value_1];
		};

		static constexpr std::size_t type_tuple_size = 1 + sizeof...(Types);
	};
	template <typename... Types>
	constexpr inline type_tuple<Types...> type_tuple_v = {};

	template <typename... Types>
	constexpr auto get(value_wrap auto i, type_tuple<Types...> t) noexcept
	{
		return t[i];
	};
	template <typename... Types>
	constexpr auto element_implementation(value_wrap auto i, type_tuple<Types...> t) noexcept
	{
		return PP_DECLTYPE(get(i, t));
	};
	constexpr auto size_implementation(type_wrap auto t) noexcept
	requires requires { PP_GET_TYPE(t)::type_tuple_size; }
	{
		return PP_GET_TYPE(t)::type_tuple_size;
	};
}
