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

	template <typename F>
	constexpr auto operator!(const functor<F>& f) noexcept
	{
		return negate | f;
	}
	template <typename F>
	constexpr auto operator!(const functor<F>&& f) noexcept
	{
		return negate | std::move(f);
	}
}
