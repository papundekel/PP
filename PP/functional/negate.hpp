#pragma once
#include "compose.hpp"
#include "functor.hpp"
#include "operators.hpp"

namespace PP
{
	constexpr auto operator!(concepts::functor auto&& f) noexcept
	{
		return neg | PP_FORWARD(f);
	}
}
