#pragma once
#include "get_type.hpp"
#include "tuple_recursive.hpp"
#include "tuple_head_no_get.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	template <typename...>
	struct type_tuple_t {};
	template <typename Head, typename... Rest>
	struct type_tuple_t<Head, Rest...>
	{
		type_tuple_t() = default;
		constexpr type_tuple_t(type_t<Head>, type_t<Rest>...) noexcept
		{}

		constexpr auto head() const noexcept
		{
			return type<Head>;
		}
		constexpr auto head_element() const noexcept
		{
			return type<type_t<Head>>;
		}
		constexpr auto pred() const noexcept
		{
			return type_tuple_t<Rest...>{};
		}
		constexpr auto operator[](concepts::value auto i) const noexcept
		{
			return tuple_recursive(tuple_head_no_get, i, *this);
		}
	};
	template <typename... T>
	type_tuple_t(type_t<T>...) -> type_tuple_t<T...>;

	template <typename... T>
	constexpr inline type_tuple_t<T...> type_tuple = {};

	template <typename... T>
	constexpr auto tuple_count_implementation(type_tuple_t<T...> t) noexcept
	{
		return value<sizeof...(T)>;
	};

	PP_FUNCTOR(make_type_tuple, concepts::type auto... t)
	{
		return type_tuple_t(to_type_t(t)...);
	}};
}
