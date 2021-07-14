#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "functor.hpp"
#include "operators.hpp"

namespace PP
{
	// PP_FUNCTOR(negate, auto&& f)
	//{
	//	return compose(neg, PP_FORWARD(f));
	//});

	constexpr inline auto negate = compose * neg;

	constexpr auto operator!(concepts::functor auto&& f) noexcept
	{
		return negate(PP_FORWARD(f));
	}
}
