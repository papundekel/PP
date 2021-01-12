#pragma once
#include <array>
#include "value_t.hpp"
#include "get_value.hpp"

namespace PP::detail
{
	template <typename T>
	struct is_std_array_helper : public value_t<false> {};
	template <typename T, std::size_t N>
	struct is_std_array_helper<std::array<T, N>> : public value_t<true> {};

	template <typename T>
	concept is_std_array = get_value<is_std_array_helper<std::remove_cvref_t<T>>>();
}

namespace std
{
	template <std::size_t I, PP::detail::is_std_array A>
	constexpr decltype(auto) get(PP::value_t<I>, A&& a) noexcept
	{
		return std::get<I>(std::forward<A>(a));
	}
}