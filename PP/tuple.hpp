#pragma once
#include <tuple>
#include "value_t.hpp"
#include "get_value.hpp"

namespace PP::detail
{
	template <typename T>
	struct is_std_tuple_helper : public value_t<false> {};
	template <typename... Types>
	struct is_std_tuple_helper<std::tuple<Types...>> : public value_t<true> {};

	template <typename T>
	concept is_std_tuple = get_value<is_std_tuple_helper<std::remove_cvref_t<T>>>();
}

namespace std
{
	template <std::size_t I>
	constexpr decltype(auto) get(PP::value_t<I>, PP::detail::is_std_tuple auto&& tuple)
	{
		return std::get<I>(std::forward<decltype(tuple)>(tuple));
	}
}
