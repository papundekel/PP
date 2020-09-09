#pragma once

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept has_value_f = requires
		{
			T::value_f();
		};
		template <typename T>
		concept has_value = requires
		{
			T::value;
		};

		struct get_value__no_value_member {};
	}
	template <typename T>
	requires (detail::has_value_f<T>)
	constexpr decltype(auto) get_value() noexcept
	{
		return T::value_f();
	}
	template <typename T>
	requires (!detail::has_value_f<T> && detail::has_value<T>)
	constexpr decltype(auto) get_value() noexcept
	{
		return (T::value);
	}
	template <typename T>
	constexpr detail::get_value__no_value_member get_value() noexcept
	{
		return {};
	}
}
