#pragma once
#include "view.hpp"

namespace PP
{
	PP_FUNCTOR(view_find, auto&& predicate, concepts::view auto&& v)
	{
		auto i = view_begin(PP_FORWARD(v));

		for (; i != view_end(PP_FORWARD(v)) && !PP_FORWARD(predicate)(*i); ++i);

		return move(i);
	});
}
