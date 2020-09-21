#pragma once
#include <utility>

namespace PP
{
	constexpr inline auto equal =
		[]<typename X, typename Y>(X&& x, Y&& y)
		{
			return std::forward<X>(x) == std::forward<Y>(y);
		};
}
