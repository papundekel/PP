#pragma once

namespace detail
{
	template <typename T, typename U, typename ...V>
	constexpr bool same = same<T, U> && same<U, V...>;

	template <typename T, typename U>
	constexpr bool same<T, U> = false;

	template <typename T>
	constexpr bool same<T, T> = true;
}

template <typename T, typename U, typename ...V>
concept same = detail::same<T, U, V...>;

template <typename T, typename U, typename ...V>
concept other_than = !same<T, U, V...>;