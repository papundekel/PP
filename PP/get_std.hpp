#pragma once
#include "size_t.hpp"
#include "tuple_like.hpp"

namespace PP
{
	template <size_t I>
	constexpr decltype(auto) get(concepts::tuple auto&& t) noexcept
	{
		return PP_FORWARD(t)[value<I>];
	}
}
