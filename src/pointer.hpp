#pragma once

namespace detail
{
	template <typename T>
	constexpr bool pointer = false;

	template <typename T>
	constexpr bool pointer<T*> = true;
}

template <typename T>
concept pointer = detail::pointer<T>;