#pragma once
#include <utility>

namespace PP
{
	constexpr inline auto equal =
		[](auto&& x, auto&& y)
		{
			return std::forward<decltype(x)>(x) == std::forward<decltype(y)>(y);
		};
}
