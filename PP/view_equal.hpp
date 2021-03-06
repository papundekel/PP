#pragma once
#include "view_first_equal.hpp"
#include "zip_iterator_std.hpp"

namespace PP
{
	PP_FUNCTOR(view_equal_if, auto&& comparer, concepts::view auto&& a, concepts::view auto&& b)
	{
		auto [ai, bi] = view_first_difference_if(PP_FORWARD(comparer), PP_FORWARD(a), PP_FORWARD(b));

		return ai == view_end(PP_FORWARD(a)) && bi == view_end(PP_FORWARD(b));
	});

	constexpr inline auto view_equal = view_equal_if * eql;
}
