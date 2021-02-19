#pragma once
#include "tuple_fold.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_for_each, concepts::value auto left, auto&& f, concepts::tuple auto&& t)
	{
		tuple_fold(left, [&f]
			(auto, auto&& element)
			{
				PP_FORWARD(f)(PP_FORWARD(element));
				return 0;
			}, 0, PP_FORWARD(t));
	}};
}
