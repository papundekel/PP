#pragma once
#include <utility>

namespace PP
{
	template <bool copy = true>
	constexpr inline auto constant =
		[](auto c)
		{
			return[c = std::move(c)](auto&&...){ return c; };
		};
	template <>
	constexpr inline auto constant<false> =
		[](auto& c)
		{
			return[&c](auto&&...){ return c; };
		};
}