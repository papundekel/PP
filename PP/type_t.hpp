#pragma once

namespace PP
{
	template <typename T>
	struct type_t
	{
		using type = T;

		constexpr auto operator->() const noexcept;
	};
	template <typename T>
	constexpr inline type_t<T> type = {};

	constexpr inline type_t<void> type_void = {};

	template <typename T, typename U>
	constexpr auto operator==(type_t<T>, type_t<U>) noexcept
	{
		return false;
	}
	template <typename T>
	constexpr auto operator==(type_t<T>, type_t<T>) noexcept
	{
		return true;
	}

	#define PP_TYPE_UNSAFE(x) typename decltype(x)::type
	#define PP_DECLTYPE(x) (::PP::type<decltype(x)>)
}
