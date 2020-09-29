#pragma once
#include <utility>

namespace PP
{
	template <bool copy_first = true, bool copy_second = true>
	constexpr inline auto compose = [](auto& f, auto& g)
	{
		return [&f, &g]<typename... T>(T&&... t) -> decltype(auto)
		{
			return f(g(std::forward<T>(t)...));
		};
	};
	template <>
	constexpr inline auto compose<false, true> = [](auto& f, auto&& g)
	{
		return [&f, g = std::forward<decltype(g)>(g)]<typename... T>(T&&... t) -> decltype(auto)
		{
			return compose<false, false>(f, g)(std::forward<T>(t)...);
		};
	};
	template <>
	constexpr inline auto compose<true, false> = [](auto&& f, auto& g)
	{
		return [f = std::forward<decltype(f)>(f), &g]<typename... T>(T&&... t) -> decltype(auto)
		{
			return compose<false, false>(f, g)(std::forward<T>(t)...);
		};
	};
	template <>
	constexpr inline auto compose<true, true> = [](auto&& f, auto&& g)
	{
		return [f = std::forward<decltype(f)>(f), g = std::forward<decltype(g)>(g)]<typename... T>(T&&... t) -> decltype(auto)
		{
			return compose<false, false>(f, g)(std::forward<T>(t)...);
		};
	};

	constexpr auto operator|(auto& f, auto& g) noexcept
	{
		return compose<false, false>(f, g);
	}

	constexpr auto operator||(auto&& f, auto&& g) noexcept
	{
		return compose<>(std::forward<decltype(f)>(f), std::forward<decltype(g)>(g));
	}
}
