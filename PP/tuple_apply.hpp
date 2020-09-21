#pragma once
#include <tuple>

namespace PP
{
	constexpr inline auto tuple_apply =
		[]<typename F, typename T>(F&& f, T&& t) -> decltype(auto)
		{
			return std::apply(std::forward<F>(f), std::forward<T>(t));
		};
}
