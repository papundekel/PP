#pragma once
#include "functional/functor.hpp"
#include "get_value.hpp"
#include "tuple_head_no_get.hpp"
#include "tuple_recursive.hpp"
#include "value_t.hpp"

namespace PP
{
	template <auto...>
	struct value_tuple_t
	{};
	template <auto Head, auto... Rest>
	struct value_tuple_t<Head, Rest...>
	{
		value_tuple_t() = default;
		constexpr value_tuple_t(value_t<Head>, value_t<Rest>...) noexcept
		{}

		constexpr auto head() const noexcept
		{
			return value<Head>;
		}
		constexpr auto head_element() const noexcept
		{
			return type<value_t<Head>>;
		}
		constexpr auto pred() const noexcept
		{
			return value_tuple_t<Rest...>{};
		}
		constexpr auto operator[](concepts::value auto i) const noexcept
		{
			return tuple_recursive(tuple_head_no_get, i, *this);
		}
	};
	template <auto... V>
	value_tuple_t(value_t<V>...) -> value_tuple_t<V...>;

	template <auto... Values>
	constexpr inline auto value_tuple = value_tuple_t<Values...>{};

	template <auto... V>
	constexpr auto tuple_count_implementation(value_tuple_t<V...>) noexcept
	{
		return value<sizeof...(V)>;
	}

	PP_FUNCTOR(make_value_tuple, concepts::value auto... v)
	{
		return value_tuple_t(to_value_t(v)...);
	});
}
