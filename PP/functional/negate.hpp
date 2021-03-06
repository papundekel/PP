#pragma once
#include "compose.hpp"
#include "functor.hpp"
#include "operators.hpp"

namespace PP
{
	PP_FUNCTOR(negate, auto&& f)
	{
		return compose(neg, PP_FORWARD(f));
	});

	constexpr auto operator!(concepts::functor auto&& f) noexcept
	{
		return negate(PP_FORWARD(f));
	}
}
