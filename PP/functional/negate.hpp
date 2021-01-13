#pragma once
#include "compose.hpp"

namespace PP
{
	constexpr inline functor negate
	{
		[](auto&& t) -> decltype(auto)
		{
			return !PP_FORWARD(t);
		}
	};

	constexpr auto operator!(is_functor auto&& f) noexcept
	{
		return negate | PP_FORWARD(f);
	}
}
