#pragma once
#include <tuple>

namespace PP
{
	template <typename F, typename Tuple>
	constexpr auto tuple_for_each(F&& f, Tuple&& tuple)
	{
		return std::apply(
			[&f]<typename... T>(T&&... t)
			{
				(std::forward<F>(f)(std::forward<T>(t)), ...);
			}, std::forward<Tuple>(tuple));
	}
}
