#pragma once
#include "empty.hpp"
#include "view_fold.hpp"

namespace PP
{
	PP_FUNCTOR(view_for_each, auto&& f, concepts::view auto&& v)
	{
		return view_fold(
			value_true,
			[&f](empty, auto&& x)
			{
				PP_F(f)(PP_F(x));
				return empty{};
			},
			empty{},
			PP_F(v))[value_0];
	});
}
