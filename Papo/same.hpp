#pragma once

namespace Papo
{
	namespace detail
	{
		template <typename T, typename U>
		inline constexpr auto same = false;
		template <typename T>
		inline constexpr auto same<T, T> = true;
	}
	template <typename T, typename U>
	concept same = detail::same<T, U>;
}
