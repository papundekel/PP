#pragma once

namespace detail
{
	template <typename T>
	constexpr bool reference_lvalue = false;

	template <typename T>
	constexpr bool reference_lvalue<T&> = true;
}

template <typename T>
concept reference_lvalue = detail::reference_lvalue<T>;