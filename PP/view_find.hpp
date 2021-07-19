#pragma once
#include "view.hpp"

namespace PP
{
	PP_FUNCTOR(view_find, auto&& predicate, concepts::view auto&& v)
	{
		auto i = view_begin(PP_F(v));

		for (; i != view_end(PP_F(v)) && !PP_F(predicate)(*i); ++i)
			;

		return move(i);
	});
}
