#pragma once
#include <utility>

namespace PP
{
	template <bool copy_first = true, bool copy_second = true>
	constexpr inline auto compose = [](auto f, auto g)
	{
		return [f = std::move(f), g = std::move(g)]<typename... T>(T&&... t) -> decltype(auto)
		{
			return f(g(std::forward<T>(t)...));
		};
	};
	template <>
	constexpr inline auto compose<false, true> = [](auto& f, auto g) noexcept
	{
		return [&f, g = std::move(g)]<typename... T>(T&&... t) -> decltype(auto)
		{
			return f(g(std::forward<T>(t)...));
		};
	};
	template <>
	constexpr inline auto compose<true, false> = [](auto f, auto& g) noexcept
	{
		return [f = std::move(f), &g]<typename... T>(T&&... t) -> decltype(auto)
		{
			return f(g(std::forward<T>(t)...));
		};
	};
	template <>
	constexpr inline auto compose<false, false> = [](auto& f, auto& g) noexcept
	{
		return [&f, &g]<typename... T>(T&&... t) -> decltype(auto)
		{
			return f(g(std::forward<T>(t)...));
		};
	};

	template <typename F, typename G>
	constexpr auto operator|(F& f, G& g) noexcept
	{
		return compose<false, false>(f, g);
	}

	constexpr auto operator||(auto f, auto g) noexcept
	{
		return compose<>(std::move(f), std::move(g));
	}
}
