#pragma once
#include "value_t.hpp"

namespace PP
{
	template <std::size_t I>
	constexpr decltype(auto) get(auto&& t) noexcept
	{
		return get(value_v<I>, PP_FORWARD(t));
	}
}
