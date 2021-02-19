#pragma once
#include "view_first_difference.hpp"

namespace PP
{
	constexpr bool view_equal(concepts::view auto&& a, concepts::view auto&& b)
	{
		auto [ai, bi] = view_first_difference(PP_FORWARD(a), PP_FORWARD(b));

		return ai == view_end(PP_FORWARD(a)) && bi == view_end(PP_FORWARD(b));
	}
}
