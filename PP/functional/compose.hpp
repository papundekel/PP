#pragma once
#include <utility>

namespace PP
{
	template <typename F, typename G>
	constexpr auto operator|(F&& f, G&& g) noexcept
	{
		return [&f, &g]<typename... T>(T&&... t) -> decltype(auto)
		{
			return std::forward<F>(f)(std::forward<G>(g)(std::forward<T>(t)...));
		};
	}

	template <typename F, typename G>
	constexpr auto operator||(F&& f, G&& g) noexcept
	{
		return[f = std::forward<F>(f), g = std::forward<G>(g)]<typename... T>(T&&... t) -> decltype(auto)
		{
			return f(g(std::forward<T>(t)...));
		};
	}

	template <typename... F>
	constexpr auto compose(F&&... f) noexcept
	{
		return (std::forward<F>(f) || ... || id_weak);
	}
	template <typename... F>
	constexpr auto compose_no_copy(F&&... f) noexcept
	{
		return (std::forward<F>(f) | ... | id_weak);
	}
}
