#pragma once

namespace detail
{
	template <typename T>
	constexpr bool const_t = false;

	template <typename T>
	constexpr bool const_t<const T> = true;
}

template <typename T>
concept const_t = detail::const_t<T>;