#pragma once
#include "view_first_equal.hpp"

namespace PP
{
	PP_FUNCTOR(view_prefix, concepts::view auto&& v, concepts::view auto&& prefix)
	{
		return view_first_difference(PP_FORWARD(v), PP_FORWARD(prefix))[value_1] == view_end(PP_FORWARD(prefix));
	});
}
