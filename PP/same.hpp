#pragma once

namespace PP
{
	namespace detail
	{
		template <typename T, typename U>
		constexpr inline bool same = false;
		template <typename T>
		constexpr inline bool same<T, T> = true;
	}
	template <typename T, typename U>
	concept same = detail::same<T, U> && detail::same<U, T>;
}
