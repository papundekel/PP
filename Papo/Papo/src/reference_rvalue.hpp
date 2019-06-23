#pragma once

namespace detail
{
	template <typename T>
	constexpr bool reference_rvalue = false;

	template <typename T>
	constexpr bool reference_rvalue<T&&> = true;
}

template <typename T>
concept reference_rvalue = detail::reference_rvalue<T>;