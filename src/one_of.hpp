#pragma once
#include "same.hpp"

namespace detail
{
	template <typename T, typename U, typename ...V>
	constexpr bool one_of = same<T, U> || one_of<T, V...>;

	template <typename T, typename U>
	constexpr bool one_of<T, U> = same<T, U>;
}

template <typename T, typename U, typename ...V>
concept one_of = detail::one_of<T, U, V...>;