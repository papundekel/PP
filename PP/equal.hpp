#pragma once
#include "view.hpp"

namespace PP
{
	constexpr bool equal(concepts::view auto&& a, concepts::view auto&& b)
	{
		auto [ai, ae] = view_begin_end(PP_FORWARD(a));
		auto [bi, be] = view_begin_end(PP_FORWARD(b));

		for (; ai != ae && bi != be; ++ai, ++bi)
			if (*ai != *bi)
				return false;

		return ai == ae && bi == be;
	}
}
